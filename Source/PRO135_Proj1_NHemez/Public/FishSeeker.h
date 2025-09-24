// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoatPawn.h"
#include "FishPawn.h"
#include "FishSeeker.generated.h"

/**
 * 
 */
UCLASS()
class PRO135_PROJ1_NHEMEZ_API AFishSeeker : public AFishPawn
{
	GENERATED_BODY()

public:

protected:
	
	virtual void BeginPlay() override;

	ABoatPawn* Target = nullptr;
	
public:

	virtual void Tick(float DeltaTime) override;
	
};
