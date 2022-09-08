// Fill out your copyright notice in the Description page of Project Settings.


#include "EMPlayerController.h"

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

	}
}

void AEMPlayerController::SelectObjectStart()
{
	IsLeftMousePressed = true;
}
void AEMPlayerController::SelectObjectStop()
{
	IsLeftMousePressed = false;
}

void AEMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SelectObject", IE_Pressed, this, &AEMPlayerController::SelectObjectStart);
	InputComponent->BindAction("SelectObject", IE_Released, this, &AEMPlayerController::SelectObjectStop);
}


