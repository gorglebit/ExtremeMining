// Fill out your copyright notice in the Description page of Project Settings.

#include "EMPlayerController.h"
#include "GameFramework/HUD.h"
#include "EMHeadUpDisplay.h"

AEMPlayerController::AEMPlayerController()
{
	IsLeftMousePressed = false;
}

void AEMPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	FInputModeGameAndUI inputMode = FInputModeGameAndUI();
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	inputMode.SetHideCursorDuringCapture(false);
	
	SetInputMode(inputMode);
	SetShowMouseCursor(true);
}

void AEMPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AEMHeadUpDisplay* HUD = Cast<AEMHeadUpDisplay>(GetHUD());
	if (!HUD) return;

	if (IsLeftMousePressed)
	{
		HUD->MarqueeHeld();
	}
}

void AEMPlayerController::SelectObjectStart()
{
	IsLeftMousePressed = true;
	//UE_LOG(LogTemp, Warning, TEXT("LeftMouse = true"));

	AEMHeadUpDisplay* HUD = Cast<AEMHeadUpDisplay>(GetHUD());
	if (!HUD) return;

	HUD->MarqueePressed();
}
void AEMPlayerController::SelectObjectStop()
{
	IsLeftMousePressed = false;
	//UE_LOG(LogTemp, Warning, TEXT("LeftMouse = false"));

	AEMHeadUpDisplay* HUD = Cast<AEMHeadUpDisplay>(GetHUD());
	if (!HUD) return;

	HUD->MarqueeReleased();
}

void AEMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SelectObject", IE_Pressed, this, &AEMPlayerController::SelectObjectStart);
	InputComponent->BindAction("SelectObject", IE_Released, this, &AEMPlayerController::SelectObjectStop);
}


