// Fill out your copyright notice in the Description page of Project Settings.

#include "EMUserWidgetBase.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"

#include "../Building/EMBuildingStorage.h"

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

void UEMUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
}

