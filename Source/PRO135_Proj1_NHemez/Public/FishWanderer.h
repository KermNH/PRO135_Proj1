// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoatPawn.h"
#include "FishPawn.h"
#include "FishWanderer.generated.h"

/**
 * 
 */
UCLASS()
class PRO135_PROJ1_NHEMEZ_API AFishWanderer : public AFishPawn
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;

	ABoatPawn* Target = nullptr;

	FVector PointToGoTo;
	FVector Direction;
	
public:

	virtual void Tick(float DeltaTime) override;
	
};
