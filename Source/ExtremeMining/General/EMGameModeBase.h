// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EMGameModeBase.generated.h"

class UUserWidget;

UCLASS()
class EXTREMEMINING_API AEMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

protected:
    virtual void BeginPlay() override;
};
