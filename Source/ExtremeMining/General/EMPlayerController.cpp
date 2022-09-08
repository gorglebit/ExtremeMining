// Fill out your copyright notice in the Description page of Project Settings.

#include "EMPlayerController.h"
#include "GameFramework/HUD.h"
#include "EMHeadUpDisplay.h"

void AEMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	IsLeftMousePressed = false;
	FInputModeGameAndUI date;
	SetInputMode(date);
	SetShowMouseCursor(true);

}

void AEMPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLeftMousePressed)
	{
		SelectionHeld();
	}
}

void AEMPlayerController::SelectObjectStart()
{
	IsLeftMousePressed = true;

	AEMHeadUpDisplay* HUD = Cast<AEMHeadUpDisplay>(GetHUD());
	if (!HUD) return;

	HUD->SelectionPressed();
}
void AEMPlayerController::SelectObjectStop()
{
	IsLeftMousePressed = false;

	AEMHeadUpDisplay* HUD = Cast<AEMHeadUpDisplay>(GetHUD());
	if (!HUD) return;

	SelectionReleased();
}

void AEMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SelectObject", IE_Pressed, this, &AEMPlayerController::SelectObjectStart);
	InputComponent->BindAction("SelectObject", IE_Released, this, &AEMPlayerController::SelectObjectStop);
}


