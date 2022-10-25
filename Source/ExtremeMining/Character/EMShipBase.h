// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interface/EMBasicInterface.h"
#include "EMShipBase.generated.h"

class UWidgetComponent;

UCLASS()
class EXTREMEMINING_API AEMShipBase : public ACharacter, public IEMBasicInterface
{
	GENERATED_BODY()
private:
	FTimerHandle CheckLandTimer;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UWidgetComponent* ShipWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UStaticMeshComponent* BodyMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		USceneComponent* FirstSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		USceneComponent* SecondSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		USceneComponent* ThirdSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsButtonVisible;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsCanDropped;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector SpawnPassengersLocation;

	int32 CurrentNumberOfPassangers;
	int32 MaxNumberOfPassangers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<AEMCharacterBase*> PassengersOnBoardArray;
public:

	//-----------------------

private:
protected:
	UFUNCTION()
	void OnDropOffPassangers();

	virtual void BeginPlay() override;

	void SetGetOffButtonTimer();
public:
	AEMShipBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SelectObject() override;

	virtual void DeselectObject() override;

	virtual void UnitMoveCommand(const FVector Location) override;

	FORCEINLINE int32 GetCurrentNumberOfPassangers() { return CurrentNumberOfPassangers; }
	FORCEINLINE int32 GetMaxNumberOfPassangers() { return MaxNumberOfPassangers; }

	void TakePassengerOnBoard(AEMCharacterBase* InPassenger);
	void SeatPassengerOnPlace(AEMCharacterBase* InPassenger, USceneComponent* InScene);

	UFUNCTION(BlueprintNativeEvent)
		void SetSailVisual();

	UFUNCTION(BlueprintNativeEvent)
		void SetLandButtonVisibitity();
};
