// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Interface/EMBasicInterface.h"
#include "EMBuildingBase.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UWidgetComponent;

UCLASS()
class EXTREMEMINING_API AEMBuildingBase : public AActor, public IEMBasicInterface
{
	GENERATED_BODY()

private:
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* BuildMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		UBoxComponent* CollisionBoxComponent;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 BuildingType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 BuildingLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 BuildingMaxLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 FirstUpgradeLevelCost;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 SecondUpgradeLevelCost;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 ThirdUpgradeLevelCost;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UWidgetComponent* BuildingWidget;
public:

//------------------------

private:
	void SetCitizenMaxCount(const int32 InLevel);

protected:
	virtual void BeginPlay() override;

public:
	AEMBuildingBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SelectObject() override;

	virtual void DeselectObject() override;

	void UpgradeBuilding();


	FORCEINLINE UBoxComponent* GetBoxComponent() { return CollisionBoxComponent; }

	FORCEINLINE int32 GetBuildingType() { return BuildingType; }

	FORCEINLINE int32 GetBuildingLevel() { return BuildingLevel; }

	FORCEINLINE int32 GetFirstUpgradeLevelCost() { return FirstUpgradeLevelCost; }

	FORCEINLINE int32 GetSecondUpgradeLevelCost() { return SecondUpgradeLevelCost; }

	FORCEINLINE int32 GetThirdUpgradeLevelCost() { return ThirdUpgradeLevelCost; }

	FORCEINLINE void IncrementBuildingLevel() { BuildingLevel++; BuildingLevel = FMath::Clamp(BuildingLevel, 0, 3); }
};
