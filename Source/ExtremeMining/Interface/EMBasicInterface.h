// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EMBasicInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEMBasicInterface : public UInterface
{
	GENERATED_BODY()
};

class AEMCharacterBase;

class EXTREMEMINING_API IEMBasicInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void MarqueePressed();
	virtual void MarqueeHeld();
	virtual void MarqueeReleased();

	virtual void SelectObject();
	virtual void DeselectObject();

	virtual void UnitMoveCommand(const FVector3d Location);
	virtual TArray<AEMCharacterBase*> GrabSelectedUnits();
	
	virtual void ClearSelectedBuildings();
};
