// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interface/EMBasicInterface.h"
#include "EMCharacterBase.generated.h"

class UStaticMeshComponent;
class AEMBuildingStorage;

enum CharacterType
{
	CHARACTER_MAIN,
	CHARACTER_FOOD,
	CHARACTER_WOOD,
	CHARACTER_MONEY,
	CHARACTER_SEA
};

UCLASS()
class EXTREMEMINING_API AEMCharacterBase : public ACharacter, public IEMBasicInterface
{
	GENERATED_BODY()

private:
	FTimerHandle TimerCheckMoveStatus;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UStaticMeshComponent* BodyMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		UStaticMeshComponent* HatMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Storage)
		AEMBuildingStorage* BuildingStorage;

	UPROPERTY(BlueprintReadOnly)
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
		int32 CollectionRateWorker;

	UPROPERTY(BlueprintReadWrite)
		bool IsCommandActive;

public:
	

private:
	void CheckMoveStatus();
	

protected:
	virtual void BeginPlay() override;

public:
	AEMCharacterBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SelectObject() override;

	virtual void DeselectObject() override;

	virtual void UnitMoveCommand(const FVector Location) override;

	FORCEINLINE int32 GetCharacterType() { return CharacterType; }

	FORCEINLINE void SetCharacterType(const int32 CharType) { CharacterType = CharType; }

	UFUNCTION(BlueprintNativeEvent)
		void SetCharacterRole(const int32 Type);

	void SetWorkLocation(const int32 BuildType);

	UFUNCTION(BlueprintCallable)
		void CollectResouse();
};
