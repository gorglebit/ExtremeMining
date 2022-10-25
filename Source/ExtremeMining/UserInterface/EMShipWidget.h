// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EMShipWidget.generated.h"

class UButton;

UCLASS()
class EXTREMEMINING_API UEMShipWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* GetOffButton;

public:
//----------------
private:
protected:
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UButton* GetGetOffButton() { return GetOffButton; }
};
