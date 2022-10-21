// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EMCoreActor.generated.h"

#define BUILDING_TYPE_MAIN		0
#define BUILDING_TYPE_FOOD		1
#define BUILDING_TYPE_WOOD		2
#define BUILDING_TYPE_MONEY		3
#define BUILDING_TYPE_SEA		4
#define BUILDING_TYPE_STORAGE	5

#define CHARACTER_TYPE_CITIZEN	0
#define CHARACTER_TYPE_FOOD		1
#define CHARACTER_TYPE_WOOD		2
#define CHARACTER_TYPE_MONEY	3
#define CHARACTER_TYPE_SEA		4	

UCLASS()
class EXTREMEMINING_API AEMCoreActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEMCoreActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	static float GetDistance(AActor* InActorFrom, AActor* InActorTo);
	int32 GetBuildingLevelFromType(const int32 BuildingType);

};
