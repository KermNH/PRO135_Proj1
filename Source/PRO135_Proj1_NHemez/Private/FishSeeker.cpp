// Fill out your copyright notice in the Description page of Project Settings.


#include "FishSeeker.h"

#include "BoatPawn.h"


void AFishSeeker::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<ABoatPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AFishSeeker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Target != nullptr)
	{
		MoveTowards(FVector(Target->GetActorLocation()));
	}
}


