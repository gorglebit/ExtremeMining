// Fill out your copyright notice in the Description page of Project Settings.

#include "../Core/EMCoreActor.h"

#include "Kismet/GameplayStatics.h"

#include "../Building/EMBuildingBase.h"

AEMCoreActor::AEMCoreActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEMCoreActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEMCoreActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AEMCoreActor::GetDistance(AActor* InActorFrom, AActor* InActorTo)
{
	return (InActorFrom->GetActorLocation() - InActorTo->GetActorLocation()).Size();
}

int32 AEMCoreActor::GetBuildingLevelFromType(const int32 BuildingType)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingBase::StaticClass(), OutActors);

	int32 BuildLevel = 0;
	for (int i = 0; i < OutActors.Num(); i++)
	{
		auto AsBuilding = Cast<AEMBuildingBase>(OutActors[i]);
		if (AsBuilding->GetBuildingType() == BuildingType)
		{
			BuildLevel = AsBuilding->GetBuildingLevel();
			return BuildLevel;
		}
	}
	return 0;
}

