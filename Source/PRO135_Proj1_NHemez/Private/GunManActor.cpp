// Fill out your copyright notice in the Description page of Project Settings.


#include "GunManActor.h"
#include "Components/ArrowComponent.h"

// Sets default values
AGunManActor::AGunManActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGunManActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunManActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

