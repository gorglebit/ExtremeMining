// Fill out your copyright notice in the Description page of Project Settings.

#include "EMBuildingStorage.h"
#include <Kismet/GameplayStatics.h>

#include "../General/EMHeadUpDisplay.h"
#include "../UserInterface/EMUserWidgetBase.h"
#include "../Character/EMCharacterBase.h"
#include "../General/EMPlayerState.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

void AEMBuildingStorage::SetFoodAmount(const int32 Amount)
{
	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!AsState) return;

	Food = Amount;
	Food = FMath::Clamp(Food, 0, AsState->GetMaxResourceCount());
	OnFoodAmountChangedDelegate.Broadcast(Food);

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMCharacterBase::StaticClass(), OutActors);

	if (Food <= 50)
	{
		for (int i = 0; i < OutActors.Num(); i++)
		{
			AEMCharacterBase* AsCharacter = Cast<AEMCharacterBase>(OutActors[i]);
			if (!AsCharacter) return;

			if (AsCharacter && !AsCharacter->GetIsCommandActive())
			{
				AsCharacter->SetMaxMoveSpeed(200);
				AsCharacter->SetIsHungry(true);
			}
		}
	}
	else
	{
		for (int i = 0; i < OutActors.Num(); i++)
		{
			AEMCharacterBase* AsCharacter = Cast<AEMCharacterBase>(OutActors[i]);
			if (!AsCharacter) return;

			if (AsCharacter && !AsCharacter->GetIsCommandActive())
			{
				AsCharacter->SetMaxMoveSpeed(400);
				AsCharacter->SetIsHungry(false);
			}
		}
	}

	SetFoodStorage();
}

void AEMBuildingStorage::SetWoodAmount(const int32 Amount)
{
	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!AsState) return;

	Wood = Amount;
	Wood = FMath::Clamp(Wood, 0, AsState->GetMaxResourceCount());
	OnWoodAmountChangedDelegate.Broadcast(Wood);

	SetWoodStorage();
}

void AEMBuildingStorage::SetMoneyAmount(const int32 Amount)
{
	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!AsState) return;

	Money = Amount;
	Money = FMath::Clamp(Money, 0, AsState->GetMaxResourceCount());
	OnMoneyAmountChangedDelegate.Broadcast(Money);

	SetMoneyStorage();
}

void AEMBuildingStorage::UpgradeStorage()
{
	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!AsState) return;

	switch (BuildingLevel)
	{
	case 1:
	{
		AsState->SetMaxResourceCount(500);
		break;
	}
	case 2:
	{
		AsState->SetMaxResourceCount(750);
		break;
	}
	case 3:
	{
		AsState->SetMaxResourceCount(1000);
		break;
	}
	default:
		break;
	}
}

void AEMBuildingStorage::SetWoodStorage_Implementation()
{
}

void AEMBuildingStorage::SetMoneyStorage_Implementation()
{
}

void AEMBuildingStorage::SetFoodStorage_Implementation()
{
}

void AEMBuildingStorage::BeginPlay()
{
	Super::BeginPlay();

	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));

	SetFoodAmount(AsState->GetStartResourceCount());
	SetWoodAmount(AsState->GetStartResourceCount());
	SetMoneyAmount(AsState->GetStartResourceCount());
}

void AEMBuildingStorage::SetStorageWithDelay()
{
	auto AsHud = Cast<AEMHeadUpDisplay>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	if (!AsHud) return;
	UE_LOG(LogTemp, Warning, TEXT("AsHud"));

	auto AsUserWidget = Cast<UEMUserWidgetBase>(AsHud->GetStorage());

	if (!AsUserWidget) return;
	UE_LOG(LogTemp, Warning, TEXT("UserWidget"));
	AsUserWidget->SetStorage(this);
}

AEMBuildingStorage::AEMBuildingStorage()
{
	PrimaryActorTick.bCanEverTick = true;

	Food = 0;
	Wood = 0;
	Money = 0;
}

void AEMBuildingStorage::SpendMoneyOnUpgrade(const int32 InResourceAmount)
{
	Wood = Wood - InResourceAmount;
	Money = Money - InResourceAmount;
}

	

