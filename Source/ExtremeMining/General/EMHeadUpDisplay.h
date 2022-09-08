// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "../Interface/EMHeadUpDisplayInterface.h"

#include "EMHeadUpDisplay.generated.h"

/**
 * 
 */
UCLASS()
class EXTREMEMINING_API AEMHeadUpDisplay : public AHUD, public IEMHeadUpDisplayInterface
{
	GENERATED_BODY()
	
public:
	virtual void SelectionPressed() override;
	virtual void SelectionHeld() override;
	virtual void SelectionReleased() override;

	//virtual void ReceiveDrawHUD(int32 SizeX, int32 SizeY) override;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	bool IsDrawing = false;

	UPROPERTY(BlueprintReadOnly)
	FVector2D StartMousePosition = 0.0;
	UPROPERTY(BlueprintReadOnly)
	FVector2D CurrentMousePostion = 0.0;
private:
	
	

	
};
