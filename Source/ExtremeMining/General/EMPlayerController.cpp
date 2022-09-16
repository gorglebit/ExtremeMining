// Fill out your copyright notice in the Description page of Project Settings.

#include "EMPlayerController.h"
#include "GameFramework/HUD.h"
#include "EMHeadUpDisplay.h"
#include "../Character/EMCharacterBase.h"

AEMPlayerController::AEMPlayerController()
{
	IsLeftMousePressed = false;
	RightMouseLocation = { 0,0,0 };
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

void AEMPlayerController::SelectObjectStartAction()
{
	IsLeftMousePressed = true;
	//UE_LOG(LogTemp, Warning, TEXT("LeftMouse = true"));

	AEMHeadUpDisplay* HUD = Cast<AEMHeadUpDisplay>(GetHUD());
	if (!HUD) return;

	HUD->MarqueePressed();
}
void AEMPlayerController::SelectObjectStopAction()
{
	IsLeftMousePressed = false;
	//UE_LOG(LogTemp, Warning, TEXT("LeftMouse = false"));

	AEMHeadUpDisplay* HUD = Cast<AEMHeadUpDisplay>(GetHUD());
	if (!HUD) return;

	HUD->MarqueeReleased();
}

void AEMPlayerController::MoveToLocationAction()
{
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery_MAX, true, HitResult);
	RightMouseLocation = HitResult.Location;
	//UE_LOG(LogTemp, Warning, TEXT("Location - x = %f, y = %f, z = %f ,"), RightMouseLocation.X, RightMouseLocation.Y, RightMouseLocation.Z);


	AEMHeadUpDisplay* HUD = Cast<AEMHeadUpDisplay>(GetHUD());
	if (!HUD) return;

	TArray<AActor*> SelectedCharactersArray = HUD->GrabSelectedUnits();
	//UE_LOG(LogTemp, Warning, TEXT("SelectedCharactersArray size = %i"), SelectedCharactersArray.Num());
	for (int i = 0; i < SelectedCharactersArray.Num(); i++)
	{
		AEMCharacterBase* CharActer = Cast<AEMCharacterBase>(SelectedCharactersArray[i]);
		if (CharActer)
		{
			// RightMouseLocation or other formation location
			CharActer->UnitMoveCommand(RightMouseLocation);
		}
	}

	//Spawn NiagraSystem in mouse right click direction
}

void AEMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SelectObject", IE_Pressed, this, &AEMPlayerController::SelectObjectStartAction);
	InputComponent->BindAction("SelectObject", IE_Released, this, &AEMPlayerController::SelectObjectStopAction);
	InputComponent->BindAction("MoveToLocation", IE_Released, this, &AEMPlayerController::MoveToLocationAction);
}


