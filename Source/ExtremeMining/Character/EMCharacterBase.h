// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interface/EMBasicInterface.h"
#include "EMCharacterBase.generated.h"

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

	UPROPERTY(BlueprintReadWrite)
		FVector StorageLocation;

	UPROPERTY(BlueprintReadOnly)
		float WorkLocationRadius;

	UPROPERTY(BlueprintReadOnly)
		float WorkLocationDelta;

	UPROPERTY(BlueprintReadWrite)
		int32 CharacterType;

	UPROPERTY(BlueprintReadWrite)
		bool IsCommandActive;

	UPROPERTY(BlueprintReadWrite)
		bool IsHungry;

public:
	//------------------------------

private:
	void CheckMoveStatus();
	void IntakeFoodTimer();
	

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

	FORCEINLINE FTimerHandle GetCollectResourceTimer() { return CollectResourceTimer; }

	void SetIsHungry(const bool InCondition);

	FORCEINLINE int32 GetCharacterType() { return CharacterType; }

	void SetCharacterType(const int32 InCharType);

	UFUNCTION(BlueprintCallable)
		void SetWorkLocation(const int32 InCharacterType);

	UFUNCTION(BlueprintCallable)
		void SetStorageLocation();

	UFUNCTION(BlueprintCallable)
		void CollectResouseTimer();

	void SetMaxMoveSpeed(const int SpeedAmount);

	UFUNCTION(BlueprintNativeEvent)
		void SetCollectWidget(const int32 ResourceType);

	UFUNCTION(BlueprintNativeEvent)
		void SetCharacterRole(const int32 Type);

	UFUNCTION(BlueprintNativeEvent)
		void SpawnMoveCommandFX();

	void SetCollectionResource(const bool IsCollectResource);
};
