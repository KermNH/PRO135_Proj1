// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GunManComponent.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRO135_PROJ1_NHEMEZ_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void GunnerAdded(UGunManComponent* GunMan);
	
	//virtual bool Initialize() override;
};
