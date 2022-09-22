// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EMUserWidgetBase.generated.h"

class AEMBuildingStorage;

UCLASS()
class EXTREMEMINING_API UEMUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
private:
protected:
	UFUNCTION(BLueprintCallable)
		int32 GetFoodAmount();

	UFUNCTION(BLueprintCallable)
		int32 GetWoodAmount();

	UFUNCTION(BLueprintCallable)
		int32 GetMoneyAmount();
public:
private:
protected:
	UPROPERTY(BLueprintReadOnly)
		AEMBuildingStorage* BuildingStorage;
public:
	FORCEINLINE void SetStorage(AEMBuildingStorage* storage) { BuildingStorage = storage; }
};
