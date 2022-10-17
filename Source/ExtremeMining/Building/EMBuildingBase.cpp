// Fill out your copyright notice in the Description page of Project Settings.

#include "EMBuildingBase.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"

#include "../Character/EMCharacterBase.h"
#include "../General/EMPlayerState.h"
#include "../Building/EMBuildingStorage.h"
#include "../UserInterface/EMBuildingWidget.h"


//UE_LOG(LogTemp, Warning, TEXT(""));

AEMBuildingBase::AEMBuildingBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BuildMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BuildMesh->SetupAttachment(RootComponent);

	CollisionBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("EnterBoxCollision"));
	CollisionBoxComponent->SetupAttachment(BuildMesh);

	BuildingWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BuildingWidget"));
	BuildingWidget->SetupAttachment(BuildMesh);

	BuildingLevel = 0;
	BuildingMaxLevel = 3;

	FirstUpgradeLevelCost = 100;
	SecondUpgradeLevelCost = 200;
	ThirdUpgradeLevelCost = 300;
}

void AEMBuildingBase::SetCitizenMaxCount(const int32 InLevel)
{
	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!AsState) return;

	switch (InLevel)
	{
	case 1:
	{
		AsState->SetMaxCitizenCount(20);
		break;
	}
	case 2:
	{
		AsState->SetMaxCitizenCount(25);
		break;
	}
	case 3:
	{
		AsState->SetMaxCitizenCount(30);
		break;
	}
	default:
		break;
	}
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
	BuildingWidget->SetVisibility(true);
	
	auto AsWidget = Cast<UEMBuildingWidget>(BuildingWidget->GetWidget());
	if (!AsWidget) return;
	AsWidget->GetUpgradeButton()->OnClicked.AddDynamic(AsWidget, &UEMBuildingWidget::UpgradeBuilding);
}

void AEMBuildingBase::DeselectObject()
{
	BuildMesh->SetRenderCustomDepth(false);
	BuildingWidget->SetVisibility(false);

	auto AsWidget = Cast<UEMBuildingWidget>(BuildingWidget->GetWidget());
	if (!AsWidget) return;
	AsWidget->GetUpgradeButton()->OnClicked.RemoveDynamic(AsWidget, &UEMBuildingWidget::UpgradeBuilding);
}

void AEMBuildingBase::UpgradeBuilding()
{
	SpawnUpgradeFX();

	SpandMoneyOnUpgrade();
	
	IncrementBuildingLevel();

	switch (BuildingType)
	{
	case 0:
	{
		SetCitizenMaxCount(BuildingLevel);
		break;
	}
	case 5:
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingStorage::StaticClass(), OutActors);

		auto AsStorage = Cast<AEMBuildingStorage>(OutActors[0]);
		if (!AsStorage) break;
		
		AsStorage->UpgradeStorage();

		break;
	}
	default:
		break;
	}
}

void AEMBuildingBase::SpandMoneyOnUpgrade()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingStorage::StaticClass(), OutActors);

	auto AsStorage = Cast<AEMBuildingStorage>(OutActors[0]);
	if (!AsStorage) return;


	int32 UpgrageCost;
	switch (BuildingLevel)
	{
	case 0:
	{
		UpgrageCost = FirstUpgradeLevelCost;
		break;
	}
	case 1:
	{
		UpgrageCost = SecondUpgradeLevelCost;
		break;
	}
	case 2:
	{
		UpgrageCost = ThirdUpgradeLevelCost;
		break;
	}
	default:
		break;
	}

	AsStorage->SpendMoneyOnUpgrade(UpgrageCost);

}

void AEMBuildingBase::SpawnUpgradeFX_Implementation()
{
}

void AEMBuildingBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlap!"));

	AEMCharacterBase* AsCharacter = Cast<AEMCharacterBase>(OtherActor);
	if (!AsCharacter) return;

	if (BuildingType > 4)
	{
	}
	else
	{
		AsCharacter->SetCharacterType(BuildingType);
		AsCharacter->SetCharacterRole(BuildingType);
		AsCharacter->SetWorkLocation(BuildingType);
	}
}
