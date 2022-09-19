// Fill out your copyright notice in the Description page of Project Settings.

#include "EMBuildingBase.h"

AEMBuildingBase::AEMBuildingBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BuildMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BuildMesh->SetupAttachment(RootComponent);
	BuildMesh->SetRelativeRotation(FRotator(0.f, 45.f, 0.f));
}

void AEMBuildingBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEMBuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEMBuildingBase::SelectObject()
{
	BuildMesh->SetRenderCustomDepth(true);
}

void AEMBuildingBase::DeselectObject()
{
	BuildMesh->SetRenderCustomDepth(false);
}

