// Fill out your copyright notice in the Description page of Project Settings.


#include "FishPawn.h"

#include "BoatPawn.h"
#include "PirahnaHuntGameMode.h"

// Sets default values
AFishPawn::AFishPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FishMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = FishMesh;
	
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComp"));
	SteeringComponent = CreateDefaultSubobject<USteeringBehaviors>(TEXT("SteeringBehavior"));

	Life = FMath::RandRange(MinLife, MaxLife);
}

// Called when the game starts or when spawned
void AFishPawn::BeginPlay()
{
	Super::BeginPlay();
	this->OnActorBeginOverlap.AddDynamic(this, &AFishPawn::HitBoat);
	
}

void AFishPawn::ReceiveDamage(int const DamageAmount, FVector Location)
{
	Life -= DamageAmount;
	if (Life <= 0) {
		Death();
	}
	SpawnBloodFX(Location);

}

void AFishPawn::SpawnBloodFX(FVector Location) const
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			BloodFX,
			Location,
			FRotator::ZeroRotator,
			FVector(1.0f),
			true,
			true);
	
}

void AFishPawn::HitBoat(AActor* MyActor, AActor* OtherActor)
{
	if (Cast<ABoatPawn>(OtherActor))
	{
		ABoatPawn* target = Cast<ABoatPawn>(OtherActor);
		target->ReceiveDamage(1, this);
		Destroy();
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Hit something else");
	}
}

void AFishPawn::Death()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			DeathFX,
			this->GetActorLocation(),
			FRotator::ZeroRotator,
			FVector(1.0f),
			true,
			true);
	Cast<APirahnaHuntGameMode>(GetWorld()->GetAuthGameMode())->Score += ScoreToGive;
	Destroy();
}

// Called every frame
void AFishPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFishPawn::MoveTowards(const FVector& Target)
{
	FVector Steering = SteeringComponent->Seek(Target);
	MovementComponent->AddInputVector(Steering);
	
	if (MovementComponent->Velocity != FVector::ZeroVector)
	{
		FRotator NewRotation = MovementComponent->Velocity.Rotation(); // Get rotation from velocity vector
		SetActorRotation(NewRotation);
	}		
	//float Speed = Steering.Size();
	//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "Moving towards target at speed " + FString::SanitizeFloat(Speed));
}

// Called to bind functionality to input
//void AFishPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

