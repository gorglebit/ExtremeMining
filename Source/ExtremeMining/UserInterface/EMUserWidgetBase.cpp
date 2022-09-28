// Fill out your copyright notice in the Description page of Project Settings.

#include "EMUserWidgetBase.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"

#include "../Building/EMBuildingStorage.h"
#include "../General/EMPlayerState.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

int32 UEMUserWidgetBase::GetFoodAmount()
{
	if (!StorageBuilding) return 0;

	return StorageBuilding->GetFoodAmount();
}

int32 UEMUserWidgetBase::GetWoodAmount()
{
	if (!StorageBuilding) return 0;

	return StorageBuilding->GetWoodAmount();
}

int32 UEMUserWidgetBase::GetMoneyAmount()
{
	if (!StorageBuilding) return 0;

	return StorageBuilding->GetMoneyAmount();
}

void UEMUserWidgetBase::OnFoodAmountChanged(int32 NewAmount)
{
	if (NewAmount <= 50)
	{
		FoodTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
	}
	else
	{
		FoodTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	}

	FoodTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnWoodAmountChanged(int32 NewAmount)
{
	if (NewAmount <= 50)
	{
		WoodTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
	}
	else
	{
		WoodTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	}

	WoodTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnMoneyAmountChanged(int32 NewAmount)
{
	if (NewAmount <= 50)
	{
		MoneyTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
	}
	else
	{
		MoneyTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	}

	MoneyTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnCurrentCitizenCountChanged(int32 NewAmount)
{
	CurrentCitizenTextBlock->SetText(FText::AsNumber(NewAmount));
	//UE_LOG(LogTemp, Warning, TEXT("CurrentCitizenTextBlock->SetText"));
}

void UEMUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingStorage::StaticClass(), OutActors);
	StorageBuilding = Cast<AEMBuildingStorage>(OutActors[0]);
	
	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));

	CurrentCitizenTextBlock->SetText(FText::AsNumber(AsState->GetStartCitizenCount()));
	MaxCitizenTextBlock->SetText(FText::AsNumber(AsState->GetMaxCitizenCount()));

	FoodTextBlock->SetText(FText::AsNumber(AsState->GetStartResourceCount()));
	WoodTextBlock->SetText(FText::AsNumber(AsState->GetStartResourceCount()));
	MoneyTextBlock->SetText(FText::AsNumber(AsState->GetStartResourceCount()));

	if (StorageBuilding)
	{
		StorageBuilding->OnFoodAmountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnFoodAmountChanged);
		StorageBuilding->OnWoodAmountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnWoodAmountChanged);
		StorageBuilding->OnMoneyAmountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnMoneyAmountChanged);
		
		AsState->OnCurrentCitizenCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnCurrentCitizenCountChanged);
		
		//UE_LOG(LogTemp, Warning, TEXT("OnFoodAmountChangedDelegate"));
	}
		
}

