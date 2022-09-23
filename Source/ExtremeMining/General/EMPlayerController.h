// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "../Interface/EMBasicInterface.h"
#include "EMPlayerController.generated.h"

class AEMBuildingBase;

UCLASS()
class EXTREMEMINING_API AEMPlayerController : public APlayerController, public IEMBasicInterface
{
	GENERATED_BODY()

private:
	bool IsLeftMousePressed;
	FVector RightMouseLocation;
	AEMBuildingBase* SelectedBuilding;
protected:
public:
//------------------

private:
	void SelectObjectStartAction();
	void SelectObjectStopAction();
	void MoveToLocationAction();

protected:
	virtual void BeginPlay() override;

public:
	AEMPlayerController();

	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	void ClearSelectedBuildings() override;
};
