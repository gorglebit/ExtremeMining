// Fill out your copyright notice in the Description page of Project Settings.


#include "EMBasicInterface.h"

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

TArray<AActor*> IEMBasicInterface::GrabSelectedUnits()
{
	return TArray<AActor*>();
}