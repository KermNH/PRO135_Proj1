// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimerManager.h"
#include "FishPawn.h"
#include "PirahnaHuntGameMode.generated.h"


/**
 * 
 */
UCLASS()
class PRO135_PROJ1_NHEMEZ_API APirahnaHuntGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Varaibles",  meta = (AllowPrivateAccess = true))
	float TailleRadius = 5000.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFishPawn> ObjectToSpawn;

	UPROPERTY(EditAnywhere)
	float MinTimebeforeSpawn = 2.0f;

	UPROPERTY(EditAnywhere)
	float MaxTimebeforeSpawn = 2.0f;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AFishPawn>> FishToSpawn;
	


public:
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Varaibles", meta = (AllowPrivateAccess = true))
	int Score = 0;

protected:

	virtual void BeginPlay() override;
	
	UFUNCTION()
	FVector FindRandomPoint();

	FTimerHandle SpawnTimer;

	float SpawnInterval;

private:
	void SpawnFish();
	
};
