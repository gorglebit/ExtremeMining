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

UCLASS()
class EXTREMEMINING_API AEMBuildingBase : public AActor, public IEMBasicInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BuildMesh;

protected:

public:
	UPROPERTY(BlueprintReadWrite)
		int32 BuildingType;

public:	
	AEMBuildingBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SelectObject() override;

	virtual void DeselectObject() override;

};
