// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "NiagaraFunctionLibrary.h"
#include "SteeringBehaviors.h"
#include "FishPawn.generated.h"

UCLASS()
class PRO135_PROJ1_NHEMEZ_API AFishPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FishMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, Blueprintable, Category="Components", meta = (AllowPrivateAccess = "true"))
	USteeringBehaviors* SteeringComponent;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    int MinLife = 100.0f;
    	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxLife = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VFX", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* BloodFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VFX", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* DeathFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VFX", meta = (AllowPrivateAccess = "true"))

	int ScoreToGive = 2;


protected:
	
	int Life;

public:
	// Sets default values for this pawn's properties
	AFishPawn();
	
	UFUNCTION()
	void HitBoat(AActor* MyActor, AActor* OtherActor);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Death();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveTowards(const FVector& Target);

	void ReceiveDamage(int const DamageAmount, FVector Location);

	void SpawnBloodFX(FVector Location) const;


	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
