// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../Interface/EMBasicInterface.h"
#include "EMCharacterBase.generated.h"

#define BUILDING_TYPE_FOOD	1
#define BUILDING_TYPE_WOOD	2
#define BUILDING_TYPE_MONEY 3

#define CHARACTER_TYPE_CITIZEN	0
#define CHARACTER_TYPE_FOOD		1
#define CHARACTER_TYPE_WOOD		2
#define CHARACTER_TYPE_MONEY	3
#define CHARACTER_TYPE_SEA		4	

class UStaticMeshComponent;
class AEMBuildingStorage;

UCLASS()
class EXTREMEMINING_API AEMCharacterBase : public ACharacter, public IEMBasicInterface
{
	GENERATED_BODY()

private:
	FTimerHandle CheckMoveStatusTimer;
	FTimerHandle FoodIntakeTimer;
	FTimerHandle CollectResourceTimer;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UStaticMeshComponent* BodyMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UStaticMeshComponent* HatMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Storage)
		AEMBuildingStorage* StorageBuilding;

	UPROPERTY(BlueprintReadWrite)
		FVector WorkLocation;

	UPROPERTY(BlueprintReadOnly)
		float WorkLocationRadius;

	UPROPERTY(BlueprintReadOnly)
		float WorkLocationDelta;

	UPROPERTY(BlueprintReadWrite)
		int32 CharacterType;

	UPROPERTY(BlueprintReadWrite)
		int32 CollectionRateNotWorker;

	UPROPERTY(BlueprintReadWrite)
		int32 CollectionRateWorkerFood;

	UPROPERTY(BlueprintReadWrite)
		int32 CollectionRateWorkerWood;

	UPROPERTY(BlueprintReadWrite)
		int32 CollectionRateWorkerMoney;

	UPROPERTY(BlueprintReadWrite)
		int32 CollectionRateWorkerDelta;

	UPROPERTY(BlueprintReadWrite)
		int32 CollectionRateWorkerStart;

	UPROPERTY(BlueprintReadWrite)
		int32 FoodIntakeCount;

	UPROPERTY(BlueprintReadWrite)
		bool IsCommandActive;

	UPROPERTY(BlueprintReadWrite)
		bool IsHungry;

public:
	//------------------------------

private:
	void CheckMoveStatus();
	void IntakeFood();
	int32 GetBuildingLevel(const int32 BuildingType);

protected:
	virtual void BeginPlay() override;

public:
	AEMCharacterBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SelectObject() override;

	virtual void DeselectObject() override;

	virtual void UnitMoveCommand(const FVector Location) override;

	FORCEINLINE bool GetIsCommandActive() { return IsCommandActive; }

	FORCEINLINE bool GetIsHungry() { return IsHungry; }

	FORCEINLINE void SetIsHungry(bool InCondition) { IsHungry = InCondition; }

	FORCEINLINE int32 GetCharacterType() { return CharacterType; }

	FORCEINLINE void SetCharacterType(const int32 InCharType) { CharacterType = InCharType; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetCollectionReateWorkerFood() { return CollectionRateWorkerFood; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetCollectionReateWorkerWood() { return CollectionRateWorkerWood; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetCollectionReateWorkerMoney() { return CollectionRateWorkerMoney; }

	FORCEINLINE void SetCollectionReateWorkerFood(const int32 InAmount) { CollectionRateWorkerFood = InAmount; }
	FORCEINLINE void SetCollectionReateWorkerWood(const int32 InAmount) { CollectionRateWorkerWood = InAmount; }
	FORCEINLINE void SetCollectionReateWorkerMoney(const int32 InAmount) { CollectionRateWorkerMoney = InAmount; }

	UFUNCTION(BlueprintCallable)
	void SetWorkLocation(const int32 InCharacterType);

	UFUNCTION(BlueprintCallable)
		void CollectResouse();



	void SetMaxMoveSpeed(const int SpeedAmount);

	UFUNCTION(BlueprintNativeEvent)
		void SetCollectWidget(const int32 ResourceType);

	UFUNCTION(BlueprintNativeEvent)
		void SetCharacterRole(const int32 Type);
};
