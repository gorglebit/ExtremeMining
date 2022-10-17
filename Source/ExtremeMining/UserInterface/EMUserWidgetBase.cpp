// Fill out your copyright notice in the Description page of Project Settings.

#include "EMUserWidgetBase.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"

#include "../Character/EMCharacterBase.h"
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

void UEMUserWidgetBase::OnMaxRecourceCountChanged(int32 NewAmount)
{
	MaxFoodTextBlock->SetText(FText::AsNumber(NewAmount));
	MaxWoodTextBlock->SetText(FText::AsNumber(NewAmount));
	MaxMoneyTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnCurrentCitizenCountChanged(int32 NewAmount)
{
	CurrentCitizenTextBlock->SetText(FText::AsNumber(NewAmount));
	//UE_LOG(LogTemp, Warning, TEXT("CurrentCitizenTextBlock->SetText"));
}

void UEMUserWidgetBase::OnMaxCitizenCountChanged(int32 NewAmount)
{
	MaxCitizenTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnCitizenFoodCountChanged(int32 NewAmount)
{
	CitizenFoodTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnCitizenWoodCountChanged(int32 NewAmount)
{
	CitizenWoodTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnCitizenMoneyCountChanged(int32 NewAmount)
{
	CitizenMoneyTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnCitizenNoneCountChanged(int32 NewAmount)
{
	CitizenNoneTextBlock->SetText(FText::AsNumber(NewAmount));
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
	CitizenNoneTextBlock->SetText(FText::AsNumber(AsState->GetStartCitizenCount()));

	FoodTextBlock->SetText(FText::AsNumber(AsState->GetStartResourceCount()));
	WoodTextBlock->SetText(FText::AsNumber(AsState->GetStartResourceCount()));
	MoneyTextBlock->SetText(FText::AsNumber(AsState->GetStartResourceCount()));

	MaxFoodTextBlock->SetText(FText::AsNumber(AsState->GetMaxResourceCount()));
	MaxWoodTextBlock->SetText(FText::AsNumber(AsState->GetMaxResourceCount()));
	MaxMoneyTextBlock->SetText(FText::AsNumber(AsState->GetMaxResourceCount()));

	if (StorageBuilding)
	{
		StorageBuilding->OnFoodAmountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnFoodAmountChanged);
		StorageBuilding->OnWoodAmountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnWoodAmountChanged);
		StorageBuilding->OnMoneyAmountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnMoneyAmountChanged);
		
		AsState->OnMaxResourceCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnMaxRecourceCountChanged);
		AsState->OnCurrentCitizenCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnCurrentCitizenCountChanged);
		AsState->OnMaxCitizenCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnMaxCitizenCountChanged);
		
		AsState->OnCitizenFoodCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnCitizenFoodCountChanged);
		AsState->OnCitizenWoodCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnCitizenWoodCountChanged);
		AsState->OnCitizenMoneyCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnCitizenMoneyCountChanged);
		AsState->OnCitizenNoneCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnCitizenNoneCountChanged);
		//UE_LOG(LogTemp, Warning, TEXT("OnFoodAmountChangedDelegate"));
	}
		
}

