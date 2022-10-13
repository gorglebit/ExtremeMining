// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EMBuildingWidget.generated.h"

class UTextBlock;
class UHorizontalBox;
class UButton;
class AEMBuildingStorage;

UCLASS()
class EXTREMEMINING_API UEMBuildingWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	bool IsUpgrading;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* WoodCountTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* MoneyCountTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UHorizontalBox* UpgradeHorizontalBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* UpgradeButton;

	UPROPERTY(BLueprintReadOnly)
		AEMBuildingStorage* StorageBuilding;
public:
	//-----------------------
private:
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetResourceCount();

	UFUNCTION(BlueprintCallable)
		void SetUpgrageButtonEnable();

	UFUNCTION(BlueprintCallable)
		void UpgradeBuilding();

	UFUNCTION(BlueprintNativeEvent)
		void SetUpgradeButtonIcon(const bool IsEnable);

	UFUNCTION(BlueprintNativeEvent)
		void SetStarCount(const int32 InBuildingLevel);
public:

};
