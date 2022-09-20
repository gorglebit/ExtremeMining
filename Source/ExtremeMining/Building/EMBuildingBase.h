// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/EMBasicInterface.h"
#include "EMBuildingBase.generated.h"

enum BuildingType
{
	BUILDING_MAIN,
	BUILDING_FOOD,
	BUILDING_WOOD,
	BUILDING_MONEY,
	BUILDING_SEA
};

class UStaticMeshComponent;
class UBoxComponent;

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

	UPROPERTY(BlueprintReadWrite)
		int32 BuildingType;
public:


public:
	AEMBuildingBase();

	FORCEINLINE UBoxComponent* GetBoxComponent() { return CollisionBoxComponent; }

	FORCEINLINE int32 GetBuildingType() { return BuildingType; }

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SelectObject() override;

	virtual void DeselectObject() override;

};
