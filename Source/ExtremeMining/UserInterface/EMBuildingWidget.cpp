// Fill out your copyright notice in the Description page of Project Settings.
#include "../UserInterface/EMBuildingWidget.h"

#include "Components/TextBlock.h"
#include <Kismet/GameplayStatics.h>
#include "Components/HorizontalBox.h"
#include "Components/Button.h"

#include "../General/EMPlayerController.h"
#include "../Building/EMBuildingBase.h"
#include "../Building/EMBuildingStorage.h"


//UE_LOG(LogTemp, Warning, TEXT(""));

void UEMBuildingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingStorage::StaticClass(), OutActors);
	StorageBuilding = Cast<AEMBuildingStorage>(OutActors[0]);

	UpgradeButton->SetIsEnabled(false);

	UpgradeButton->OnClicked.AddDynamic(this, &UEMBuildingWidget::UpgradeBuilding);
}

void UEMBuildingWidget::SetResourceCount()
{
	AEMPlayerController* AsController = Cast<AEMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!AsController) return;
	
	AEMBuildingBase* SelectedBuilding = AsController->GetSelectedBuilding();
	if (!SelectedBuilding) return;
	
	int32 BuildingLevel = SelectedBuilding->GetBuildingLevel();

	switch (BuildingLevel)
	{
	case 0:
	{
		int32 count = SelectedBuilding->GetFirstUpgradeLevelCost();
		WoodCountTextBlock->SetText(FText::AsNumber(count));
		MoneyCountTextBlock->SetText(FText::AsNumber(count));

		break;
	}
	case 1:
	{
		int32 count = SelectedBuilding->GetSecondUpgradeLevelCost();
		WoodCountTextBlock->SetText(FText::AsNumber(count));
		MoneyCountTextBlock->SetText(FText::AsNumber(count));
		break;
	}
	case 2:
	{
		int32 count = SelectedBuilding->GetThirdUpgradeLevelCost();
		WoodCountTextBlock->SetText(FText::AsNumber(count));
		MoneyCountTextBlock->SetText(FText::AsNumber(count));
		break;
	}
	case 3:
	{
		UpgradeHorizontalBox->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
	default:
		break;
	}
}

void UEMBuildingWidget::SetUpgrageButtonEnable()
{
	AEMPlayerController* AsController = Cast<AEMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!AsController) return;
	
	AEMBuildingBase* SelectedBuilding = AsController->GetSelectedBuilding();
	if (!SelectedBuilding) return;

	int32 MoneyToUpgrade = SelectedBuilding->GetFirstUpgradeLevelCost() * (SelectedBuilding->GetBuildingLevel() + 1);
	int32 WoodToUpgrade = SelectedBuilding->GetFirstUpgradeLevelCost() * (SelectedBuilding->GetBuildingLevel() + 1);

	if (StorageBuilding->GetMoneyAmount() > MoneyToUpgrade && StorageBuilding->GetWoodAmount() > WoodToUpgrade)
	{
		UpgradeButton->SetIsEnabled(true);
		SetUpgradeButtonIcon(true);
	}
	else
	{
		UpgradeButton->SetIsEnabled(false);
		SetUpgradeButtonIcon(false);
	}
}

void UEMBuildingWidget::UpgradeBuilding()
{
	AEMPlayerController* AsController = Cast<AEMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!AsController) return;

	AEMBuildingBase* SelectedBuilding = AsController->GetSelectedBuilding();
	if (!SelectedBuilding) return;

	SelectedBuilding->UpgradeBuilding();

	SetStarCount(SelectedBuilding->GetBuildingLevel());
}

void UEMBuildingWidget::SetStarCount_Implementation(const int32 InBuildingLevel)
{
}

void UEMBuildingWidget::SetUpgradeButtonIcon_Implementation(const bool IsEnable)
{
}
