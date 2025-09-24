// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "SteeringBehaviors.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRO135_PROJ1_NHEMEZ_API USteeringBehaviors : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables", meta = (AllowPrivateAccess = "true"))
	float ArrivalRadius = 300.0f;

public:	
	// Sets default values for this component's properties
	USteeringBehaviors();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* Owner = nullptr;
	UFloatingPawnMovement* MovementComp;

	static float MapRangeClamped(float Value, float InMin, float InMax, float OutMin, float OutMax)
	{
		if (Value < InMin) return OutMin;
		if (Value > InMax) return OutMax;
		return OutMin + (OutMax - OutMin) * ((Value - InMin) / (InMax - InMin));
	}

	float ArriveLandingRadius = 300.0f;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector SteeringBehaviors(FVector Direction) const;
	FVector Seek(FVector Direction) const;

		
};
