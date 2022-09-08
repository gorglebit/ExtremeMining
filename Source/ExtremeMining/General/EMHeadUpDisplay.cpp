// Fill out your copyright notice in the Description page of Project Settings.

#include "EMHeadUpDisplay.h"

#include <Kismet/GameplayStatics.h>

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

//void AEMHeadUpDisplay::ReceiveDrawHUD(int32 SizeX, int32 SizeY)
//{
//	int x, y;
//	Super::ReceiveDrawHUD(x,y);
//
//	if (IsDrawing)
//	{
//		float rectHeight = CurrentMousePostion.Y - StartMousePosition.Y;
//		float rectWeight = CurrentMousePostion.X - StartMousePosition.X;
//		DrawRect(FColor::Blue, StartMousePosition.X, StartMousePosition.Y, rectWeight, rectHeight);
//	}
//}