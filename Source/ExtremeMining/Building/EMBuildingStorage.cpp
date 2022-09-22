// Fill out your copyright notice in the Description page of Project Settings.


#include "EMBuildingStorage.h"
#include <Kismet/GameplayStatics.h>

#include "../General/EMHeadUpDisplay.h"
#include "../UserInterface/EMUserWidgetBase.h"

void AEMBuildingStorage::BeginPlay()
{
	Super::BeginPlay();

	/*auto AsHud = Cast<AEMHeadUpDisplay>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (!AsHud) return;
	auto UserWidget = Cast<UEMUserWidgetBase>(AsHud->GetStorage());
	if (!UserWidget) return;
	UserWidget->SetStorage(this);*/
}

AEMBuildingStorage::AEMBuildingStorage()
{
	Food = 200;
	Wood = 200;
	Money = 200;
}
