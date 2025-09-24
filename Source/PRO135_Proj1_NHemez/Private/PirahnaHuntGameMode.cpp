// Fill out your copyright notice in the Description page of Project Settings.


#include "PirahnaHuntGameMode.h"

#include "FishPawn.h"

void APirahnaHuntGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnInterval = 2.0f;

	// Set a timer to call SpawnFish every 2 seconds
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &APirahnaHuntGameMode::SpawnFish, SpawnInterval, true);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Game Started!"));
	//CreateWidget<U
	
}

FVector APirahnaHuntGameMode::FindRandomPoint()
{
	float angle = FMath::RandRange(0.0f, 2 * PI);
	//float radius = FMath::RandRange(0.0f, TailleRadius);
	float radius = TailleRadius; 
	
	float x = radius * FMath::Cos(angle);
	float y = radius * FMath::Sin(angle);

	return FVector(x, y, 0.0f); // Assuming Z=0 for a flat plane
}

void APirahnaHuntGameMode::SpawnFish()
{
	SpawnInterval = FMath::RandRange(MinTimebeforeSpawn, MaxTimebeforeSpawn);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &APirahnaHuntGameMode::SpawnFish, SpawnInterval, true);
	if (ObjectToSpawn)
	{
		int index = rand() % FishToSpawn.Num();
		//ObjectToSpawn = FishToSpawn[index];
		GetWorld()->SpawnActor<AFishPawn>(FishToSpawn[index], FindRandomPoint(), FRotator::ZeroRotator);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Fish Spawned!"));
	}
	
}

