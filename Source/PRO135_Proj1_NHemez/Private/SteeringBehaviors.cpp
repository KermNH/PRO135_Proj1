// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringBehaviors.h"

// Sets default values for this component's properties
USteeringBehaviors::USteeringBehaviors()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	if (GetOwner()){
		Owner = GetOwner();
		MovementComp = GetOwner()->FindComponentByClass<UFloatingPawnMovement>();
	}

	// ...
}


// Called when the game starts
void USteeringBehaviors::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USteeringBehaviors::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FVector USteeringBehaviors::SteeringBehaviors(FVector Target) const
{
	FVector DesiredVelocity = Target - Owner->GetActorLocation();
	// Seek if not in landing radius
	if (DesiredVelocity.Length() > ArrivalRadius )
	{
		return Seek(Target);
	}
	
	// Ajust speed according to distance
	float Speed = MapRangeClamped(DesiredVelocity.Length(), 0,
	ArrivalRadius, 0, MovementComp->MaxSpeed);
	FVector SteeringForce = DesiredVelocity - Owner->GetVelocity();
	SteeringForce.Normalize();
	SteeringForce *= Speed;
	SteeringForce = SteeringForce.GetClampedToMaxSize(MovementComp->MaxSpeed);
	return SteeringForce;
}

FVector USteeringBehaviors::Seek(FVector const Target) const
{
	// 1. calculate the desired velocity
	FVector VDesired = Target - Owner->GetActorLocation();
	
	// 2. normalize the desired velocity
	VDesired.Normalize();
	
	// 3. scale the desired velocity to the maximum speed
	VDesired *= MovementComp->MaxSpeed;
	
	// 4. calculate the steering force
	FVector VSteering = VDesired - MovementComp->Velocity;
	// 5. Limit Steering force to Max speed
	VSteering = VSteering.GetClampedToMaxSize(MovementComp->MaxSpeed);
	
	
	return VSteering;
}




