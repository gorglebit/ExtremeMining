// Fill out your copyright notice in the Description page of Project Settings.

#include "EMHeadUpDisplay.h"

#include <Kismet/GameplayStatics.h>

#include "../Character/EMCharacterBase.h"

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
		ActorsInRectArray.Empty();
		float rectWeight = CurrentMousePostion.X - StartMousePosition.X;
		float rectHeight = CurrentMousePostion.Y - StartMousePosition.Y;
		DrawRect(FLinearColor(255, 0, 0, 0.2), StartMousePosition.X, StartMousePosition.Y, rectWeight, rectHeight);

		GetActorsInSelectionRectangle(StartMousePosition, CurrentMousePostion, ActorsInRectArray, false, false);
		
		UE_LOG(LogTemp, Warning, TEXT("ActorsInRectArray size = %i"), ActorsInRectArray.Num());

		for (int i = 0; i < ActorsInRectArray.Num(); i++)
		{
			AEMCharacterBase* CharActor = Cast<AEMCharacterBase>(ActorsInRectArray[i]);

			if (CharActor)
			{
				CharActor->SelectObject();

				SelectedObjectsArray.AddUnique(CharActor);
			}
		}

		int32 selectedArraySize = SelectedObjectsArray.Num();
		UE_LOG(LogTemp, Warning, TEXT("SelectedObjectsArray size = %i"), selectedArraySize);

		for (int i = 0; i < SelectedObjectsArray.Num(); i++)
		{
			if (ActorsInRectArray.Find(SelectedObjectsArray[i]) == -1)
			{
				AEMCharacterBase* CharActor = Cast<AEMCharacterBase>(SelectedObjectsArray[i]);
				if (CharActor)
				{
					CharActor->DeselectObject();
					SelectedObjectsArray.Remove(CharActor);
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