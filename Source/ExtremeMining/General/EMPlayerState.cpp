// Fill out your copyright notice in the Description page of Project Settings.

#include "EMPlayerState.h"

#include "Kismet/GameplayStatics.h"

#include "../Core/EMCoreActor.h"
#include "../General/EMPlayerState.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

void AEMPlayerState::FoodResourceIncomeCalculationTimer()
{
	int32 FoodIncome = CitizenFoodCount * GetCollectionRateWorker(BUILDING_TYPE_FOOD) * (IncomeTimePeriod / 5);
	int32 FoodConsumption = CurrentCitizenCount * FoodConsumptionCount * 6;
	int32 Result = FoodIncome - FoodConsumption;
	
	OnFoodIncomeChangedDelegate.Broadcast(Result);
}

void AEMPlayerState::WoodResourceIncomeCalculationTimer()
{
	int32 WoodIncome = CitizenWoodCount * GetCollectionRateWorker(BUILDING_TYPE_WOOD) * (IncomeTimePeriod / 5);
	int32 WoodConsumption = 0;
	int32 Result = WoodIncome - WoodConsumption;

	OnWoodIncomeChangedDelegate.Broadcast(Result);
}

void AEMPlayerState::MoneyResourceIncomeCalculationTimer()
{
	int32 MoneyIncome = CitizenMoneyCount * GetCollectionRateWorker(BUILDING_TYPE_MONEY) * (IncomeTimePeriod / 5);
	int32 MoneyConsumption = 0;
	int32 Result = MoneyIncome - MoneyConsumption;

	OnMoneyIncomeChangedDelegate.Broadcast(Result);
}

void AEMPlayerState::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(FoodIncomeCalculationTimer, this, &AEMPlayerState::FoodResourceIncomeCalculationTimer, 1.f, true);
	GetWorldTimerManager().SetTimer(WoodIncomeCalculationTimer, this, &AEMPlayerState::WoodResourceIncomeCalculationTimer, 1.f, true);
	GetWorldTimerManager().SetTimer(MoneyIncomeCalculationTimer, this, &AEMPlayerState::MoneyResourceIncomeCalculationTimer, 1.f, true);
}

AEMPlayerState::AEMPlayerState()
{
	//Resources
	StartResourceCount = 100;
	MaxResourceCount = 250;
	//-----------------

	//Citizen
	CurrentCitizenCount = 0;
	StartCitizenCount = 4;
	MaxCitizenCount = 15;

	CitizenNoneCount = 0;
	CitizenFoodCount = 0;
	CitizenWoodCount = 0;
	CitizenMoneyCount = 0;
	//--------------------

	//Collection
	CollectionRateNotWorker = 1;
	CollectionRateWorkerStart = 5;

	CollectionRateWorkerFood = CollectionRateWorkerStart;
	CollectionRateWorkerWood = CollectionRateWorkerStart;
	CollectionRateWorkerMoney = CollectionRateWorkerStart;

	CollectionRateWorkerDelta = 2;
	ResourceCollectionPenalty = 0;

	FoodConsumptionCount = 2;

	IncomeTimePeriod = 30;
	
}

void AEMPlayerState::SetCurrentCitizenCount(const int32 InNewCount)
{
	CurrentCitizenCount = InNewCount;
	OnCurrentCitizenCountChangedDelegate.Broadcast(InNewCount);
}

void AEMPlayerState::SetMaxCitizenCount(const int32 InNewCount)
{	
	MaxCitizenCount = InNewCount;
	OnMaxCitizenCountChangedDelegate.Broadcast(InNewCount);
}

void AEMPlayerState::SetMaxResourceCount(const int32 InNewCount)
{
	MaxResourceCount = InNewCount;
	OnMaxResourceCountChangedDelegate.Broadcast(InNewCount);
}

void AEMPlayerState::IncrementCitizentCount(const int32 InCitizenType)
{
	switch (InCitizenType)
	{
	case 0:
	{
		CitizenNoneCount++;
		OnCitizenNoneCountChangedDelegate.Broadcast(CitizenNoneCount);
		break;
	}
	case 1:
	{
		CitizenFoodCount++;
		OnCitizenFoodCountChangedDelegate.Broadcast(CitizenFoodCount);
		break;
	}
	case 2:
	{
		CitizenWoodCount++;
		OnCitizenWoodCountChangedDelegate.Broadcast(CitizenWoodCount);
		break;
	}
	case 3:
	{
		CitizenMoneyCount++;
		OnCitizenMoneyCountChangedDelegate.Broadcast(CitizenMoneyCount);
		break;
	}
	case 4:
	{
		break;
	}

	default:
		break;
	}
}

void AEMPlayerState::DecrementCitizentCount(const int32 InCitizenType)
{
	switch (InCitizenType)
	{
	case 0:
	{
		CitizenNoneCount--;
		OnCitizenNoneCountChangedDelegate.Broadcast(CitizenNoneCount);
		break;
	}
	case 1:
	{
		CitizenFoodCount--;
		OnCitizenFoodCountChangedDelegate.Broadcast(CitizenFoodCount);
		break;
	}
	case 2:
	{
		CitizenWoodCount--;
		OnCitizenWoodCountChangedDelegate.Broadcast(CitizenWoodCount);
		break;
	}
	case 3:
	{
		CitizenMoneyCount--;
		OnCitizenMoneyCountChangedDelegate.Broadcast(CitizenMoneyCount);
		break;
	}
	case 4:
	{
		break;
	}

	default:
		break;
	}
}

int32 AEMPlayerState::GetCollectionRateWorker(const int32 InBuildingType)
{
	if (InBuildingType == 0) return CollectionRateNotWorker;

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMCoreActor::StaticClass(), OutActors);
	if (OutActors.Num() == 0) return 0;

	auto AsCore = Cast<AEMCoreActor>(OutActors[0]);
	if (!AsCore) return 0;

	return CollectionRateWorkerStart + AsCore->GetBuildingLevelFromType(InBuildingType) * CollectionRateWorkerDelta - ResourceCollectionPenalty;
}
