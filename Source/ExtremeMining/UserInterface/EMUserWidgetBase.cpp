// Fill out your copyright notice in the Description page of Project Settings.

#include "EMUserWidgetBase.h"
#include <Kismet/GameplayStatics.h>

#include "../Building/EMBuildingStorage.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

int32 UEMUserWidgetBase::GetFoodAmount()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingStorage::StaticClass(), OutActors);
	BuildingStorage = Cast<AEMBuildingStorage>(OutActors[0]);
	if (!BuildingStorage) return 0;

	return BuildingStorage->GetFoodAmount();
}

int32 UEMUserWidgetBase::GetWoodAmount()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingStorage::StaticClass(), OutActors);
	BuildingStorage = Cast<AEMBuildingStorage>(OutActors[0]);
	if (!BuildingStorage) return 0;

	return BuildingStorage->GetWoodAmount();
}

int32 UEMUserWidgetBase::GetMoneyAmount()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingStorage::StaticClass(), OutActors);
	BuildingStorage = Cast<AEMBuildingStorage>(OutActors[0]);

	return BuildingStorage->GetMoneyAmount();
}

