// Fill out your copyright notice in the Description page of Project Settings.


#include "../PickUp/EMPickUpActorBase.h"

void AEMPickUpActorBase::BeginPlay()
{
	Super::BeginPlay();

	ResourceCount = SetRandomCount();
	ResourceType = SetRandomType();
	SetTypeVisual(ResourceType);
}

int32 AEMPickUpActorBase::SetRandomType()
{
	return FMath::RandRange(1, 3);
}

int32 AEMPickUpActorBase::SetRandomCount()
{
	return FMath::RandRange(50, 500);
}

void AEMPickUpActorBase::SetTypeVisual_Implementation(const int32 InResourceType)
{
}

AEMPickUpActorBase::AEMPickUpActorBase()
{
	ResourceCount = 0;
	ResourceType = 0;
}

void AEMPickUpActorBase::DestroyActorAfterGrab()
{
	Destroy();
}
