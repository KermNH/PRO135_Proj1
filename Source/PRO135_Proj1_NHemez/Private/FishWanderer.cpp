// Fill out your copyright notice in the Description page of Project Settings.


#include "FishWanderer.h"
#include "BoatPawn.h"


void AFishWanderer::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		Target = Cast<ABoatPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		Direction = FVector(Target->GetActorLocation()) - this->GetActorLocation();
		PointToGoTo = this->GetActorLocation() + Direction * 1000.0f;
	}
	else
	{
		Destroy();
	}
}

void AFishWanderer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Target != nullptr)
	{
		MoveTowards(PointToGoTo);
		if (FVector::Dist(Target->GetActorLocation(), PointToGoTo) < 10.0f)
		{
			Destroy();
		}
	}
}

