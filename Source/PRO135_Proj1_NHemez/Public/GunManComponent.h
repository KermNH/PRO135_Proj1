// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GunManWidget.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GunManComponent.generated.h"

class UArrowComponent;
class UInputAction;
struct FInputActionValue;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRO135_PROJ1_NHEMEZ_API UGunManComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VFX", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* ShotFX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float RotationMax = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float RotationMin = -1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Damage = 25;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Life = 3;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UGunManWidget* MyInfo;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayShootAnim();

protected:
	
	APawn* Owner;

public:	
	// Sets default values for this component's properties
	UGunManComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void SpawnFireFX(const FVector& EndLocation) const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category="Input")
	void CanShoot(FVector2D Target);
	
	UFUNCTION(BlueprintCallable, Category="Input")
	void DoShoot(FVector2D Direction);

	UFUNCTION(BlueprintCallable, Category="Input")
	void ReceiveDamage(int const DamageAmount);

	UFUNCTION(BlueprintCallable, Category="Input")
	void Death();

		
};
