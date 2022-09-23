// Fill out your copyright notice in the Description page of Project Settings.

#include "EMBuildingBase.h"
#include "Components/BoxComponent.h"

#include "../Character/EMCharacterBase.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

AEMBuildingBase::AEMBuildingBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BuildMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BuildMesh->SetupAttachment(RootComponent);

	CollisionBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("EnterBoxCollision"));
	CollisionBoxComponent->SetupAttachment(BuildMesh);
}

void AEMBuildingBase::BeginPlay()
{
	Super::BeginPlay();
	CollisionBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEMBuildingBase::OverlapBegin);
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

void AEMBuildingBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlap!"));

	AEMCharacterBase* AsCharacter = Cast<AEMCharacterBase>(OtherActor);
	if (!AsCharacter) return;

	if (BuildingType < 1 || BuildingType > 4)
	{
	}
	else
	{
		AsCharacter->SetCharacterType(BuildingType);
		AsCharacter->SetCharacterRole(BuildingType);
		AsCharacter->SetWorkLocation(BuildingType);
	}
}
