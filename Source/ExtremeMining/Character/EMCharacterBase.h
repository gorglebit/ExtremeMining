// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../Interface/EMBasicInterface.h"
#include "EMCharacterBase.generated.h"

UCLASS()
class EXTREMEMINING_API AEMCharacterBase : public ACharacter, public IEMBasicInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEMCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void ShowThatSelected();

	UFUNCTION(BlueprintNativeEvent)
	void ShowThatDeselected();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SelectObject() override;

	virtual void DeselectObject() override;


};
