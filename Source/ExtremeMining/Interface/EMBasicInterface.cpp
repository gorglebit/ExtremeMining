// Fill out your copyright notice in the Description page of Project Settings.


#include "EMBasicInterface.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

// Add default functionality here for any IEMBasicInterface functions that are not pure virtual.

void IEMBasicInterface::MarqueePressed()
{
}

void IEMBasicInterface::MarqueeHeld()
{
}

void IEMBasicInterface::MarqueeReleased()
{
}

void IEMBasicInterface::SelectObject()
{
}

void IEMBasicInterface::DeselectObject()
{
}

void IEMBasicInterface::UnitMoveCommand(const FVector3d Location)
{
}

TArray<AEMCharacterBase*> IEMBasicInterface::GrabSelectedUnits()
{
	return TArray<AEMCharacterBase*>();
}

void IEMBasicInterface::ClearSelectedBuildings()
{
}
