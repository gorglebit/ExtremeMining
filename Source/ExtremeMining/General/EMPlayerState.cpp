// Fill out your copyright notice in the Description page of Project Settings.

#include "EMPlayerState.h"

#include "../General/EMPlayerState.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

void AEMPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

AEMPlayerState::AEMPlayerState()
{
	StartResourceCount = 100;
	MaxResourceCount = 250;

	CurrentCitizenCount = 0;
	StartCitizenCount = 4;
	MaxCitizenCount = 15;

	CitizenNoneCount = 0;
	CitizenFoodCount = 0;
	CitizenWoodCount = 0;
	CitizenMoneyCount = 0;
	
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
