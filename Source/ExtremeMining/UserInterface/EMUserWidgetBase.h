// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "EMUserWidgetBase.generated.h"

class AEMBuildingStorage;
class UTextBlock;
class UButton;

UCLASS()
class EXTREMEMINING_API UEMUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
private:
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* CitizenNoneButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* CitizenFoodButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* CitizenWoodButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* CitizenMoneyButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* FoodTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* WoodTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* MoneyTextBlock;
	//-----------------------------

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* MaxFoodTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* MaxWoodTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* MaxMoneyTextBlock;
	//--------------------------

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* CurrentCitizenTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* MaxCitizenTextBlock;

	UPROPERTY(BLueprintReadOnly)
		AEMBuildingStorage* StorageBuilding;
	//-------------------------------------------

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* CitizenFoodTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* CitizenWoodTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* CitizenMoneyTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* CitizenNoneTextBlock;
public:
//-------------------------------
private:
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		int32 GetFoodAmount();

	UFUNCTION(BlueprintCallable)
		int32 GetWoodAmount();

	UFUNCTION(BlueprintCallable)
		int32 GetMoneyAmount();

	UFUNCTION()
		void OnFoodAmountChanged(int32 NewAmount);

	UFUNCTION()
		void OnWoodAmountChanged(int32 NewAmount);

	UFUNCTION()
		void OnMoneyAmountChanged(int32 NewAmount);

	UFUNCTION()
		void OnMaxRecourceCountChanged(int32 NewAmount);

	UFUNCTION()
		void OnCurrentCitizenCountChanged(int32 NewAmount);

	UFUNCTION()
		void OnMaxCitizenCountChanged(int32 NewAmount);

	UFUNCTION()
		void OnCitizenFoodCountChanged(int32 NewAmount);

	UFUNCTION()
		void OnCitizenWoodCountChanged(int32 NewAmount);

	UFUNCTION()
		void OnCitizenMoneyCountChanged(int32 NewAmount);

	UFUNCTION()
		void OnCitizenNoneCountChanged(int32 NewAmount);

	UFUNCTION()
		void OnSelectAllNoneCitizenClicked();

	UFUNCTION()
		void OnSelectAllFoodCitizenClicked();

	UFUNCTION()
		void OnSelectAllWoodCitizenClicked();

	UFUNCTION()
		void OnSelectAllMoneyCitizenClicked();

	UFUNCTION()
		void OnSelectCitizenType(const int32 InCitizenType);

	
public:

	UFUNCTION(BLueprintCallable)
	FORCEINLINE	void SetFoodText(const int Amount) { FoodTextBlock->SetText(FText::AsNumber(Amount)); }

	UFUNCTION(BLueprintCallable)
	FORCEINLINE	void SetWoodText(const int Amount) { WoodTextBlock->SetText(FText::AsNumber(Amount)); }

	UFUNCTION(BLueprintCallable)
	FORCEINLINE	void SetMoneyText(const int Amount) { MoneyTextBlock->SetText(FText::AsNumber(Amount)); }
	
	FORCEINLINE void SetStorage(AEMBuildingStorage* storage) { StorageBuilding = storage; }
};
