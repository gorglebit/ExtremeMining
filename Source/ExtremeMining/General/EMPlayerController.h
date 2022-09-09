// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "../Interface/EMHeadUpDisplayInterface.h"
#include "EMPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EXTREMEMINING_API AEMPlayerController : public APlayerController, public IEMHeadUpDisplayInterface
{
	GENERATED_BODY()

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
	void SelectObjectStart();
	void SelectObjectStop();
	
};