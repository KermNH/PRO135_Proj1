// Fill out your copyright notice in the Description page of Project Settings.


#include "GunManComponent.h"

#include "BoatPawn.h"
#include "FishPawn.h"



// Sets default values for this component's properties
UGunManComponent::UGunManComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	if (Cast<ABoatPawn>(GetOwner()))
	{
		Owner = Cast<ABoatPawn>(GetOwner());
	}
}

// Called when the game starts
void UGunManComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGunManComponent::SpawnFireFX(const FVector& EndLocation) const
{
	UNiagaraComponent* SpawnedFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			ShotFX,
			this->GetComponentLocation(),
			FRotator::ZeroRotator,
			FVector(1.0f),
			true,
			true);
	SpawnedFX->SetVariablePosition(TEXT("EndPoint"), EndLocation);
}



// Called every frame
void UGunManComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGunManComponent::CanShoot(FVector2D Target)
{	
    FVector Forward3D = this->Owner->GetActorRightVector();
    FVector2D Forward(Forward3D.X, Forward3D.Y);
	
	FVector Location3D = this->GetComponentLocation();
	FVector2D Location(Location3D.X, Location3D.Y);
    
	FVector2D Direction = Target - Location ;
	
	Forward = Forward.GetSafeNormal();
	Direction = Direction.GetSafeNormal();
	
	if (RotationMin < FVector2D::DotProduct(Forward, Direction) && FVector2D::DotProduct(Forward, Direction) < RotationMax)
	{
		//Fire
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("FIRE"));
		DoShoot(Direction);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CAN'T FIRE"));
	}
}


void UGunManComponent::DoShoot(FVector2D Direction)
{
	FHitResult HitResult;

	FVector Direction3D = FVector(Direction.X, Direction.Y, 0.0f);
	
	FVector StartLocation = this->GetComponentLocation();
	Direction3D = Direction3D.GetSafeNormal();
	FVector EndLocation = StartLocation + Direction3D * 15000.0f;
	FCollisionQueryParams CollisionParams;
	
	CollisionParams.AddIgnoredActor(this->GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation,
	EndLocation, ECC_WorldStatic, CollisionParams);\

	FVector EndPoint = (HitResult.bBlockingHit) ? HitResult.Location : EndLocation;
	
	SpawnFireFX(EndPoint);
	
	this->SetWorldRotation(Direction3D.Rotation()+FRotator(0.0f,-90.0f,0.0f));
	PlayShootAnim();
	
	if (HitResult.bBlockingHit)
	{
	    // If it hits something, draw a red sphere at the hit location
		DrawDebugSphere(GetWorld(), HitResult.Location, 20.0f, 12, FColor::Green, false, 2.0f);
		if (AActor* HitActor = HitResult.GetActor())
		{
			GEngine->AddOnScreenDebugMessage(-1, .1f, FColor::Yellow,
				TEXT("HIT : ") + HitActor->GetName());
			if(Cast<AFishPawn>(HitActor))
			{
				Cast<AFishPawn>(HitActor)->ReceiveDamage(Damage, HitResult.Location);
			};
		}
	}
}



void UGunManComponent::ReceiveDamage(int const DamageAmount)
{
	Life -= DamageAmount;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Damage"));
	MyInfo->OnLifeChanged(Life);
	if (Life <= 0.0f)
	{
		Death();
	}
}

void UGunManComponent::Death()
{
	Cast<ABoatPawn>(Owner)->RemoveGunman(this);
	this->DestroyComponent();
}

