// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GunManPawn.generated.h"

class UArrowComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PRO135_PROJ1_NHEMEZ_API AGunManPawn : public APawn
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    UArrowComponent* Arrow;

protected:
	
	UPROPERTY(EditAnywhere, Category="Input")
	class UInputMappingContext* DefaultInputMappingContext;
	
	/** Aim Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* AimAction;

public:
	// Sets default values for this pawn's properties
	AGunManPawn();

	UArrowComponent* GetArrow() const
	{
		return Arrow;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

};
