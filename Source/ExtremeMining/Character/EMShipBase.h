// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interface/EMBasicInterface.h"
#include "EMShipBase.generated.h"

class UWidgetComponent;
class AEMBuildingStorage;
class UCapsuleComponent;

UCLASS()
class EXTREMEMINING_API AEMShipBase : public ACharacter, public IEMBasicInterface
{
	GENERATED_BODY()
private:
	FTimerHandle CheckLandTimerHandle;
	FTimerHandle WoodConsumptionTimerHandle;
	FTimerHandle MoneyConsumptionTimerHandle;
	FTimerHandle SetMaxSpeedTimerHandle;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Storage)
		AEMBuildingStorage* StorageBuilding;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UWidgetComponent* ShipWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UStaticMeshComponent* BodyMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		UCapsuleComponent* GrabResourceComponent;

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
		bool IsShipHoldEmpty;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector SpawnPassengersLocation;

	int32 CurrentNumberOfPassangers;
	int32 MaxNumberOfPassangers;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 TransportedResourceType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 TransportedResourceCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<AEMCharacterBase*> PassengersOnBoardArray;
public:

	//-----------------------

private:
protected:
	UFUNCTION()
	void OnDropOffPassangers();

	virtual void BeginPlay() override;

	UFUNCTION()
	void SetGetOffButtonTimer();

	UFUNCTION()
		void SetMaxSpeedTimer();

	UFUNCTION()
	void WoodConsumptionTimer();

	UFUNCTION()
	void MoneyConsumptionTimer();

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
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
	void GetOffPassengerFromBoard(AEMCharacterBase* InPassenger);

	void SeatPassengerOnPlace(AEMCharacterBase* InPassenger, USceneComponent* InScene);

	void GetOffPassengerFromPlace(AEMCharacterBase* InPassenger, USceneComponent* InScene);

	UFUNCTION(BlueprintCallable)
	void UnloadShip();

	UFUNCTION(BlueprintNativeEvent)
		void SetSailVisual(const bool IsVisible);

	UFUNCTION(BlueprintNativeEvent)
		void SetLandButtonVisibitity();

	UFUNCTION(BlueprintNativeEvent)
		void SetResourceOnBoardVisibility(const int32 InResourceType, const int32 InResourceCount);

	UFUNCTION(BlueprintNativeEvent)
		void CannonsVolleyAttack(const bool InIsRight);
};
