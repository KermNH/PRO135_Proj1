// Fill out your copyright notice in the Description page of Project Settings.


#include "BoatPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PirahnaHuntGameMode.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
ABoatPawn::ABoatPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = BoatMesh;
	

	GunMan01 = CreateDefaultSubobject<UGunManComponent>(TEXT("GunMan01"));
	GunMan02 = CreateDefaultSubobject<UGunManComponent>(TEXT("GunMan02"));
	GunManArray = {GunMan01, GunMan02};
	
	HitBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);
	
	GunMan01->SetupAttachment(BoatMesh,FName(TEXT("SlotFront")));
	GunMan02->SetupAttachment(BoatMesh, FName(TEXT("SlotBack")));

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComp"));
	
}

void ABoatPawn::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	DoMove(MovementVector.X, MovementVector.Y);
}

void ABoatPawn::Shoot(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Purple, TEXT("InputFire"));
	for (UGunManComponent* GunMan : GunManArray)
	{
		GunMan->CanShoot(MouseScreenTOWorldLocation());
	}
}

FVector2D ABoatPawn::MouseScreenTOWorldLocation() const
{
	float MouseX, MouseY;
	Cast<APlayerController>(GetController())->GetMousePosition(MouseX, MouseY);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow,
		TEXT("Mouse X : ") + FString::SanitizeFloat(MouseX) + TEXT(" - Mouse Y : ") + FString::SanitizeFloat(MouseY));

	
	int32 ViewportSizeX, ViewportSizeY;
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector WorldLocation = FVector(0,0,0);
	FVector WorldDirection = FVector(0,0,1);

	if (PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY,WorldLocation, WorldDirection))
	{
		MouseX = WorldLocation.X;
		MouseY = WorldLocation.Y;
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow,
			TEXT("World X : ") + FString::SanitizeFloat(MouseX) + TEXT(" - World Y : ") + FString::SanitizeFloat(MouseY));
	}
	return(FVector2D(MouseX, MouseY));
}


// Called when the game starts or when spawned
void ABoatPawn::BeginPlay()
{
	Super::BeginPlay();	
	
	if (Cast<APlayerController>(GetController()))
	{
		PlayerController = Cast<APlayerController>(GetController());
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (DefaultInputMappingContext)
			{
				Subsystem->AddMappingContext(DefaultInputMappingContext, 0);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No System found"));
		}

		if (MainWidgetClass) // TSubclassOf<UUserWidget> set in Blueprint
		{
			MainWidget = CreateWidget<UGameWidget>(GetWorld(), MainWidgetClass);
			if (MainWidget)
			{
				MainWidget->AddToViewport();

				for (UGunManComponent* GunMan : GunManArray)
				{
					if (GunMan)
					{
						if (MainWidget->IsValidLowLevelFast())
						{
							MainWidget->GunnerAdded(GunMan);
						}
				
					}
				}
			}
		}
		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No PlayerController found"));
	}
	
}

void ABoatPawn::Death()
{
	this->Destroy();
}

void ABoatPawn::SpawnHitFX(FVector Location) const
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			HitFX,
			Location,
			FRotator::ZeroRotator,
			FVector(1.0f),
			true,
			true);
}

// Called every frame
void ABoatPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}



// Called to bind functionality to input
void ABoatPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABoatPawn::Move);
		
		//Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ABoatPawn::Shoot);
	}
}

void ABoatPawn::DoMove(const float Right, const float Forward)
{
	if (GetController() != nullptr)
	{		
		// add movement 
		AddMovementInput(FVector(1,0,0), Forward);
		AddMovementInput(FVector(0,1,0), Right);
		
		if (MovementComponent->Velocity != FVector::ZeroVector)
		{
			FRotator NewRotation = MovementComponent->Velocity.Rotation() + FRotator(0.0f,-90.0f, 0.0f); // Get rotation from velocity vector
			SetActorRotation(NewRotation);
		}		
	}
}


void ABoatPawn::ReceiveDamage(int const DamageAmount, AActor* DamageCauser)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Boat took damage : ") + FString::SanitizeFloat(DamageAmount));
	GetNearestGunman(DamageCauser->GetActorLocation())->ReceiveDamage(DamageAmount);
	SpawnHitFX(DamageCauser->GetActorLocation());
	
}

UGunManComponent* ABoatPawn::GetNearestGunman(FVector WorldLocation) const
{
	UGunManComponent* NearestGunMan = nullptr;
	float NearestDistance = FLT_MAX;

	FVector2D LocationTwoD = FVector2D(WorldLocation.X, WorldLocation.Y);
	
	for (UGunManComponent* GunMan : GunManArray)
	{

		FVector2D LocationTwoDGun = FVector2D(GunMan->GetComponentLocation().X, WorldLocation.Y);
		float Distance = FVector2D::Distance(LocationTwoDGun, LocationTwoD);
		if (Distance < NearestDistance)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT(" Nouvelle distance plus petite"));
			NearestDistance = Distance;
			NearestGunMan = GunMan;
		}
	}
	return NearestGunMan;
}

void ABoatPawn::RemoveGunman(UGunManComponent* Gunman)
{
	GunManArray.Remove(Gunman);
	if (GunManArray.Num() <= 0)
	{
		Cast<APirahnaHuntGameMode>(GetWorld()->GetAuthGameMode())->GameOver();
		Death();
	}
}
