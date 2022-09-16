// Fill out your copyright notice in the Description page of Project Settings.

#include "EMHeadUpDisplay.h"
#include <Kismet/GameplayStatics.h>
#include "../Character/EMCharacterBase.h"
#include "EMPlayerController.h"

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

		ActorsInRectArray.Empty();
		DrawRect(FLinearColor(255, 0, 0, 0.2), StartMousePosition.X, StartMousePosition.Y, rectWeight, rectHeight);

		GetActorsInSelectionRectangle(StartMousePosition, CurrentMousePostion, ActorsInRectArray, false, false);

		for (int i = 0; i < ActorsInRectArray.Num(); i++)
		{
			AEMCharacterBase* CharActor = Cast<AEMCharacterBase>(ActorsInRectArray[i]);

			if (CharActor)
			{
				CharActor->SelectObject();
				SelectedCharactersArray.AddUnique(CharActor);

				AEMPlayerController* Controller = Cast<AEMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				if (Controller)
				{
					Controller->ClearSelectedBuildings();
				}
					
			}
		}

		for (int i = 0; i < SelectedCharactersArray.Num(); i++)
		{
			if (ActorsInRectArray.Find(SelectedCharactersArray[i]) == -1)
			{
				AEMCharacterBase* CharActor = Cast<AEMCharacterBase>(SelectedCharactersArray[i]);
				if (CharActor)
				{
					CharActor->DeselectObject();
					SelectedCharactersArray.Remove(CharActor);
				}
			}
			
		}
	}
}

void AEMHeadUpDisplay::MarqueePressed()
{
	IsDrawing = true;
	float mouseX, mouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);
	StartMousePosition = { mouseX, mouseY };
	CurrentMousePostion = StartMousePosition;
}

void AEMHeadUpDisplay::MarqueeHeld()
{
	float mouseX, mouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);
	CurrentMousePostion = { mouseX, mouseY };
}

void AEMHeadUpDisplay::MarqueeReleased()
{
	IsDrawing = false;
}

TArray<AEMCharacterBase*> AEMHeadUpDisplay::GrabSelectedUnits()
{
	return SelectedCharactersArray;
}
