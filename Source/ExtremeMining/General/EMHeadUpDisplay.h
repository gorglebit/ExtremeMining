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
	AEMHeadUpDisplay();
	virtual void SelectionPressed() override;
	virtual void SelectionHeld() override;
	virtual void SelectionReleased() override;

	//virtual void ReceiveDrawHUD(int32 SizeX, int32 SizeY) override;
	
protected:
	UFUNCTION(BlueprintCallable)
	void SelectObjectInRect();

protected:
	UPROPERTY(BlueprintReadOnly)
	bool IsDrawing;

	UPROPERTY(BlueprintReadOnly)
	FVector2D StartMousePosition;
	UPROPERTY(BlueprintReadOnly)
	FVector2D CurrentMousePostion;
private:
	
	

	
};
