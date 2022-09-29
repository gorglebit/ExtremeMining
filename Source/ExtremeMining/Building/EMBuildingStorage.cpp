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
	Food = Amount;
	Food = FMath::Clamp(Food, 0, 1000);
	OnFoodAmountChangedDelegate.Broadcast(Food);

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMCharacterBase::StaticClass(), OutActors);

	if (Food <= 50)
	{
		for (int i = 0; i < OutActors.Num(); i++)
		{
			AEMCharacterBase* AsCharacter = Cast<AEMCharacterBase>(OutActors[i]);
			if (AsCharacter && !AsCharacter->GetIsCommandActive())
			{
				AsCharacter->SetMaxMoveSpeed(200);
				AsCharacter->SetIsHungry(true);
				AsCharacter->SetCollectionReateWorker(3);
			}
		}
	}
	else
	{
		for (int i = 0; i < OutActors.Num(); i++)
		{
			AEMCharacterBase* AsCharacter = Cast<AEMCharacterBase>(OutActors[i]);
			if (AsCharacter && !AsCharacter->GetIsCommandActive())
			{
				AsCharacter->SetMaxMoveSpeed(400);
				AsCharacter->SetIsHungry(false);
				AsCharacter->SetCollectionReateWorker(5);
			}
		}
	}

	SetFoodStorage();
}

void AEMBuildingStorage::SetWoodAmount(const int32 Amount)
{
	Wood = Amount;
	Wood = FMath::Clamp(Wood, 0, 1000);
	OnWoodAmountChangedDelegate.Broadcast(Wood);

	SetWoodStorage();
}

void AEMBuildingStorage::SetMoneyAmount(const int32 Amount)
{
	Money = Amount;
	Money = FMath::Clamp(Money, 0, 1000);
	OnMoneyAmountChangedDelegate.Broadcast(Money);

	SetMoneyStorage();
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

}
