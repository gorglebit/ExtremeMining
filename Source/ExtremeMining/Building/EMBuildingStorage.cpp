// Fill out your copyright notice in the Description page of Project Settings.


#include "EMBuildingStorage.h"
#include <Kismet/GameplayStatics.h>

#include "../General/EMHeadUpDisplay.h"
#include "../UserInterface/EMUserWidgetBase.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

void AEMBuildingStorage::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle MyTimer;
	GetWorldTimerManager().SetTimer(MyTimer, this, &AEMBuildingStorage::SetStorageWithDelay, 0.1f, false);

	SetStorageWithDelay();
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
	Food = 200;
	Wood = 200;
	Money = 200;
}
