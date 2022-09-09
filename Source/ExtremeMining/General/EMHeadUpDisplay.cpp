// Fill out your copyright notice in the Description page of Project Settings.

#include "EMHeadUpDisplay.h"

#include <Kismet/GameplayStatics.h>

AEMHeadUpDisplay::AEMHeadUpDisplay()
{
	IsDrawing = false;
	StartMousePosition = { 0, 0 };
	CurrentMousePostion = { 0, 0 };
}

void AEMHeadUpDisplay::SelectObjectInRect()
{
	if (IsDrawing)
	{
		float rectWeight = CurrentMousePostion.X - StartMousePosition.X;
		float rectHeight = CurrentMousePostion.Y - StartMousePosition.Y;
		DrawRect(FLinearColor::Black, StartMousePosition.X, StartMousePosition.Y, rectWeight, rectHeight);
	}
}

void AEMHeadUpDisplay::SelectionPressed()
{
	IsDrawing = true;
	float mouseX, mouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);
	StartMousePosition = { mouseX, mouseY };
	CurrentMousePostion = StartMousePosition;
}

void AEMHeadUpDisplay::SelectionHeld()
{
	float mouseX, mouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);
	CurrentMousePostion = { mouseX, mouseY };
}

void AEMHeadUpDisplay::SelectionReleased()
{
	IsDrawing = false;
}