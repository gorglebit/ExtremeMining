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
	StartCitizenCount = 4;
	CurrentCitizenCount = 0;
	MaxCitizenCount = 15;
}

void AEMPlayerState::SetCurrentCitizenCount(const int32 InNewCount)
{
	CurrentCitizenCount = InNewCount;
	OnCurrentCitizenCountChangedDelegate.Broadcast(InNewCount);
}

void AEMPlayerState::SetMaxCitizenCount(const int32 InNewCount)
{	
	MaxCitizenCount = InNewCount;
}
