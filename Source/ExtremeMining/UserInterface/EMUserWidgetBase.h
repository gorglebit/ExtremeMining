// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "EMUserWidgetBase.generated.h"

class AEMBuildingStorage;
class UTextBlock;

UCLASS()
class EXTREMEMINING_API UEMUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
private:
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* FoodTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* WoodTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* MoneyTextBlock;

	UPROPERTY(BLueprintReadOnly)
		AEMBuildingStorage* StorageBuilding;
public:
//-------------------------------
private:
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BLueprintCallable)
		int32 GetFoodAmount();

	UFUNCTION(BLueprintCallable)
		int32 GetWoodAmount();

	UFUNCTION(BLueprintCallable)
		int32 GetMoneyAmount();
	
public:
	UFUNCTION(BLueprintCallable)
	FORCEINLINE	void SetFoodText(const int Amount) { FoodTextBlock->SetText(FText::AsNumber(Amount)); }

	UFUNCTION(BLueprintCallable)
	FORCEINLINE	void SetWoodText(const int Amount) { WoodTextBlock->SetText(FText::AsNumber(Amount)); }

	UFUNCTION(BLueprintCallable)
	FORCEINLINE	void SetMoneyText(const int Amount) { MoneyTextBlock->SetText(FText::AsNumber(Amount)); }
	
	FORCEINLINE void SetStorage(AEMBuildingStorage* storage) { StorageBuilding = storage; }
};
