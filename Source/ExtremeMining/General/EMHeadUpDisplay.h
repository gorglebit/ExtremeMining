// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "../Interface/EMBasicInterface.h"

#include "EMHeadUpDisplay.generated.h"

/**
 * 
 */
UCLASS()
class EXTREMEMINING_API AEMHeadUpDisplay : public AHUD, public IEMBasicInterface
{
	GENERATED_BODY()
	
public:
	AEMHeadUpDisplay();
	virtual void MarqueePressed() override;
	virtual void MarqueeHeld() override; 
	virtual void MarqueeReleased() override;

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

	TArray<AActor*> SelectedObjectsArray;
	TArray<AActor*> ActorsInRectArray;
	
	

	
};
