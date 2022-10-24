// Fill out your copyright notice in the Description page of Project Settings.

#include "EMUserWidgetBase.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "../General/EMPlayerController.h"
#include "../General/EMHeadUpDisplay.h"
#include "../Character/EMCharacterBase.h"
#include "../Building/EMBuildingStorage.h"
#include "../General/EMPlayerState.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

int32 UEMUserWidgetBase::GetFoodAmount()
{
	if (!StorageBuilding) return 0;

	return StorageBuilding->GetFoodAmount();
}

int32 UEMUserWidgetBase::GetWoodAmount()
{
	if (!StorageBuilding) return 0;

	return StorageBuilding->GetWoodAmount();
}

int32 UEMUserWidgetBase::GetMoneyAmount()
{
	if (!StorageBuilding) return 0;

	return StorageBuilding->GetMoneyAmount();
}

void UEMUserWidgetBase::OnFoodAmountChanged(int32 NewAmount)
{
	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!AsState) return;

	if (NewAmount <= 50)
	{
		FoodTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
		FoodTextBlock->SetText(FText::AsNumber(NewAmount));
		return;
	}

	if (AsState->GetMaxResourceCount() - NewAmount <= 50)
	{
		FoodTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		FoodTextBlock->SetText(FText::AsNumber(NewAmount));
		return;
	}

	FoodTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	FoodTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnWoodAmountChanged(int32 NewAmount)
{
	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!AsState) return;

	if (NewAmount <= 50)
	{
		WoodTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
		WoodTextBlock->SetText(FText::AsNumber(NewAmount));
		return;
	}

	if (AsState->GetMaxResourceCount() - NewAmount <= 50)
	{
		WoodTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		WoodTextBlock->SetText(FText::AsNumber(NewAmount));
		return;
	}

	WoodTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	WoodTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnMoneyAmountChanged(int32 NewAmount)
{
	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!AsState) return;

	if (NewAmount <= 50)
	{
		MoneyTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
		MoneyTextBlock->SetText(FText::AsNumber(NewAmount));
		return;
	}

	if (AsState->GetMaxResourceCount() - NewAmount <= 50)
	{
		MoneyTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		MoneyTextBlock->SetText(FText::AsNumber(NewAmount));
		return;
	}

	MoneyTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	MoneyTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnMaxRecourceCountChanged(int32 NewAmount)
{
	MaxFoodTextBlock->SetText(FText::AsNumber(NewAmount));
	MaxWoodTextBlock->SetText(FText::AsNumber(NewAmount));
	MaxMoneyTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnCurrentCitizenCountChanged(int32 NewAmount)
{
	CurrentCitizenTextBlock->SetText(FText::AsNumber(NewAmount));
	//UE_LOG(LogTemp, Warning, TEXT("CurrentCitizenTextBlock->SetText"));
}

void UEMUserWidgetBase::OnMaxCitizenCountChanged(int32 NewAmount)
{
	MaxCitizenTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnCitizenFoodCountChanged(int32 NewAmount)
{
	CitizenFoodTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnCitizenWoodCountChanged(int32 NewAmount)
{
	CitizenWoodTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnCitizenMoneyCountChanged(int32 NewAmount)
{
	CitizenMoneyTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnCitizenNoneCountChanged(int32 NewAmount)
{
	CitizenNoneTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnFoodIncomeChanged(int32 NewAmount)
{
	if(NewAmount > 0)
		IncomeFoodSignTextBlock->SetText(FText::FromString(TEXT("+")));
	
	if (NewAmount < 0)
		IncomeFoodSignTextBlock->SetText(FText::FromString(TEXT("-")));

	if (NewAmount == 0)
		IncomeFoodSignTextBlock->SetText(FText::FromString(TEXT("+-")));
		
	NewAmount = FMath::Abs(NewAmount);
	IncomeFoodCountTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnWoodIncomeChanged(int32 NewAmount)
{
	if (NewAmount > 0)
		IncomeWoodSignTextBlock->SetText(FText::FromString(TEXT("+")));

	if (NewAmount < 0)
		IncomeWoodSignTextBlock->SetText(FText::FromString(TEXT("-")));

	if (NewAmount == 0)
		IncomeWoodSignTextBlock->SetText(FText::FromString(TEXT("+-")));

	NewAmount = FMath::Abs(NewAmount);
	IncomeWoodCountTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnMoneyIncomeChanged(int32 NewAmount)
{
	if (NewAmount > 0)
		IncomeMoneySignTextBlock->SetText(FText::FromString(TEXT("+")));

	if (NewAmount < 0)
		IncomeMoneySignTextBlock->SetText(FText::FromString(TEXT("-")));

	if (NewAmount == 0)
		IncomeMoneySignTextBlock->SetText(FText::FromString(TEXT("+-")));

	NewAmount = FMath::Abs(NewAmount);
	IncomeMoneyCountTextBlock->SetText(FText::AsNumber(NewAmount));
}

void UEMUserWidgetBase::OnSelectAllNoneCitizenClicked()
{
	OnSelectCitizenType(0);
}

void UEMUserWidgetBase::OnSelectAllFoodCitizenClicked()
{
	OnSelectCitizenType(1);
}

void UEMUserWidgetBase::OnSelectAllWoodCitizenClicked()
{
	OnSelectCitizenType(2);
}

void UEMUserWidgetBase::OnSelectAllMoneyCitizenClicked()
{
	OnSelectCitizenType(3);
}

void UEMUserWidgetBase::OnSelectCitizenType(const int32 InCitizenType)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMCharacterBase::StaticClass(), OutActors);

	if (OutActors.Num() == 0) return;

	auto AsHud = Cast<AEMHeadUpDisplay>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (!AsHud) return;
	AsHud->CleanSelectedUnits();

	auto AsController = Cast<AEMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!AsController) return;
	AsController->ClearSelectedBuildings();

	for (int i = 0; i < OutActors.Num(); i++)
	{
		auto AsCharacter = Cast<AEMCharacterBase>(OutActors[i]);
		if (!AsCharacter) return;

		if (AsCharacter->GetCharacterType() == InCitizenType)
		{
			AsCharacter->SelectObject();
			AsHud->SelectedCharactersArray.AddUnique(AsCharacter);
		}
	}
}

void UEMUserWidgetBase::CalculateIncomeResourcesTimer()
{
}

void UEMUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingStorage::StaticClass(), OutActors);
	StorageBuilding = Cast<AEMBuildingStorage>(OutActors[0]);
	
	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (AsState)
	{
		CurrentCitizenTextBlock->SetText(FText::AsNumber(AsState->GetStartCitizenCount()));
		MaxCitizenTextBlock->SetText(FText::AsNumber(AsState->GetMaxCitizenCount()));
		CitizenNoneTextBlock->SetText(FText::AsNumber(AsState->GetStartCitizenCount()));

		FoodTextBlock->SetText(FText::AsNumber(AsState->GetStartResourceCount()));
		WoodTextBlock->SetText(FText::AsNumber(AsState->GetStartResourceCount()));
		MoneyTextBlock->SetText(FText::AsNumber(AsState->GetStartResourceCount()));

		MaxFoodTextBlock->SetText(FText::AsNumber(AsState->GetMaxResourceCount()));
		MaxWoodTextBlock->SetText(FText::AsNumber(AsState->GetMaxResourceCount()));
		MaxMoneyTextBlock->SetText(FText::AsNumber(AsState->GetMaxResourceCount()));

		AsState->OnMaxResourceCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnMaxRecourceCountChanged);
		AsState->OnCurrentCitizenCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnCurrentCitizenCountChanged);
		AsState->OnMaxCitizenCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnMaxCitizenCountChanged);

		AsState->OnCitizenFoodCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnCitizenFoodCountChanged);
		AsState->OnCitizenWoodCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnCitizenWoodCountChanged);
		AsState->OnCitizenMoneyCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnCitizenMoneyCountChanged);
		AsState->OnCitizenNoneCountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnCitizenNoneCountChanged);
		
		AsState->OnFoodIncomeChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnFoodIncomeChanged);
		AsState->OnWoodIncomeChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnWoodIncomeChanged);
		AsState->OnMoneyIncomeChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnMoneyIncomeChanged);
	}

	if (StorageBuilding)
	{
		StorageBuilding->OnFoodAmountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnFoodAmountChanged);
		StorageBuilding->OnWoodAmountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnWoodAmountChanged);
		StorageBuilding->OnMoneyAmountChangedDelegate.AddUniqueDynamic(this, &UEMUserWidgetBase::OnMoneyAmountChanged);
		//UE_LOG(LogTemp, Warning, TEXT("OnFoodAmountChangedDelegate"));
	}

	CitizenNoneButton->OnClicked.AddDynamic(this, &UEMUserWidgetBase::OnSelectAllNoneCitizenClicked);	
	CitizenFoodButton->OnClicked.AddDynamic(this, &UEMUserWidgetBase::OnSelectAllFoodCitizenClicked);	
	CitizenWoodButton->OnClicked.AddDynamic(this, &UEMUserWidgetBase::OnSelectAllWoodCitizenClicked);	
	CitizenMoneyButton->OnClicked.AddDynamic(this, &UEMUserWidgetBase::OnSelectAllMoneyCitizenClicked);	


	GetWorld()->GetTimerManager().SetTimer(CalculateIncomeTimerHandle, this, &UEMUserWidgetBase::CalculateIncomeResourcesTimer, 2.f, true);
}

