// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GunManComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameWidget.h"
#include "BoatPawn.generated.h"

class UCharacterMovementComponent;
class UArrowComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PRO135_PROJ1_NHEMEZ_API ABoatPawn : public APawn
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BoatMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VFX", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* HitFX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UGunManComponent* GunMan01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UGunManComponent* GunMan02;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameWidget> MainWidgetClass;

	
	
	 
protected:

	UPROPERTY(EditAnywhere, Category="Input")
	class UInputMappingContext* DefaultInputMappingContext;

	UPROPERTY(BlueprintReadWrite, Category="UI", meta = (AllowPrivateAccess = "true"))
	UGameWidget* MainWidget;
	
	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GunMan", meta = (AllowPrivateAccess = "true"))
	TArray<UGunManComponent*> GunManArray;

	APlayerController* PlayerController;

public:

	// Sets default values for this pawn's properties
	ABoatPawn();

protected:
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	
	void Shoot(const FInputActionValue& Value);

	FVector2D MouseScreenTOWorldLocation() const;
	
	virtual void BeginPlay() override;

	void Death();

	void SpawnHitFX(FVector Location) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);
	
	void ReceiveDamage(int const DamageAmount, AActor* DamageCauser);

    UGunManComponent* GetNearestGunman(FVector WorldLocation) const;
	
	void RemoveGunman(UGunManComponent* Gunman);

};
