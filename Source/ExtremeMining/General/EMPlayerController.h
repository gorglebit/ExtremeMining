// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "../Interface/EMBasicInterface.h"
#include "EMPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EXTREMEMINING_API AEMPlayerController : public APlayerController, public IEMBasicInterface
{
	GENERATED_BODY()

private:
	FVector RightMouseLocation;

public:
	AEMPlayerController();

	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	bool IsLeftMousePressed;
private:
	void SelectObjectStartAction();
	void SelectObjectStopAction();
	void MoveToLocationAction();
	
};
