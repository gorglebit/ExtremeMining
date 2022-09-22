// Fill out your copyright notice in the Description page of Project Settings.

#include "EMUserWidgetBase.h"
#include <Kismet/GameplayStatics.h>

#include "../Building/EMBuildingStorage.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

int32 UEMUserWidgetBase::GetFoodAmount()
{
	if (!BuildingStorage) return 0;

	return BuildingStorage->GetFoodAmount();
}

int32 UEMUserWidgetBase::GetWoodAmount()
{
	if (!BuildingStorage) return 0;

	return BuildingStorage->GetWoodAmount();
}

int32 UEMUserWidgetBase::GetMoneyAmount()
{
	if (!BuildingStorage) return 0;

	return BuildingStorage->GetMoneyAmount();
}

