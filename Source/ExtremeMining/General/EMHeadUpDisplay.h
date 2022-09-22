// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "../Interface/EMBasicInterface.h"
#include "EMHeadUpDisplay.generated.h"

class AEMCharacterBase;
class UEMUserWidgetBase;

UCLASS()
class EXTREMEMINING_API AEMHeadUpDisplay : public AHUD, public IEMBasicInterface
{
	GENERATED_BODY()

private:
	TArray<AEMCharacterBase*> SelectedCharactersArray;
	TArray<AEMCharacterBase*> ActorsInRectArray;

protected:
	UPROPERTY(BlueprintReadOnly)
		bool IsDrawing;

	UPROPERTY(BlueprintReadOnly)
		FVector2D StartMousePosition;

	UPROPERTY(BlueprintReadOnly)
		FVector2D CurrentMousePostion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> UserWidgetBase;
	
	UPROPERTY(BlueprintReadOnly)
		UEMUserWidgetBase* UserWidget;
	
public:
	FORCEINLINE UEMUserWidgetBase* GetStorage() { return UserWidget; }

private:

protected:
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void SelectObjectInRect();

public:
	AEMHeadUpDisplay();
	virtual void MarqueePressed() override;
	virtual void MarqueeHeld() override; 
	virtual void MarqueeReleased() override;
	virtual TArray<AEMCharacterBase*> GrabSelectedUnits() override;
	

};
