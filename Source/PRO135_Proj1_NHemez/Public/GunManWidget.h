// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GunManWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRO135_PROJ1_NHEMEZ_API UGunManWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnLifeChanged(int NewLife);

};
