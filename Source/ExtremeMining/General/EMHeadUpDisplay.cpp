// Fill out your copyright notice in the Description page of Project Settings.

#include "EMHeadUpDisplay.h"
#include <Kismet/GameplayStatics.h>
#include "Blueprint/UserWidget.h"

#include "../Character/EMCharacterBase.h"
#include "../General/EMPlayerController.h"
#include "../UserInterface/EMUserWidgetBase.h"
#include "../Character/EMShipBase.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

AEMHeadUpDisplay::AEMHeadUpDisplay()
{
	IsDrawing = false;
	StartMousePosition = { 0, 0 };
	CurrentMousePostion = { 0, 0 };
}

void AEMHeadUpDisplay::BeginPlay()
{
	Super::BeginPlay();

	auto StartingWidget = CreateWidget<UUserWidget>(GetWorld(), UserWidgetBase);
	
	UserWidget = Cast<UEMUserWidgetBase>(StartingWidget);

	if (UserWidget)
	{
		UserWidget->AddToViewport();
	}
}

void AEMHeadUpDisplay::SelectObjectInRect()
{
	if (IsDrawing)
	{
		float rectWeight = CurrentMousePostion.X - StartMousePosition.X;
		float rectHeight = CurrentMousePostion.Y - StartMousePosition.Y;

		CitizenInRectArray.Empty();
		ShipsInRectArray.Empty();

		DrawRect(FLinearColor(255, 0, 0, 0.2), StartMousePosition.X, StartMousePosition.Y, rectWeight, rectHeight);

		GetActorsInSelectionRectangle(StartMousePosition, CurrentMousePostion, CitizenInRectArray, false, true);
		GetActorsInSelectionRectangle(StartMousePosition, CurrentMousePostion, ShipsInRectArray, false, true);
		
		for (int i = 0; i < CitizenInRectArray.Num(); i++)
		{
			AEMCharacterBase* AsCitizen = Cast<AEMCharacterBase>(CitizenInRectArray[i]);

			if (AsCitizen)
			{
				AsCitizen->SelectObject();
				SelectedCharactersArray.AddUnique(AsCitizen);

				AEMPlayerController* Controller = Cast<AEMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				if (Controller)
				{
					Controller->ClearSelectedBuildings();
				}
			}
		}

		for (int i = 0; i < SelectedCharactersArray.Num(); i++)
		{
			if (CitizenInRectArray.Find(SelectedCharactersArray[i]) == -1)
			{
				AEMCharacterBase* CharActor = Cast<AEMCharacterBase>(SelectedCharactersArray[i]);
				if (CharActor)
				{
					CharActor->DeselectObject();
					SelectedCharactersArray.Remove(CharActor);
				}
			}
		}

		//-----------------------------------------

		for (int i = 0; i < ShipsInRectArray.Num(); i++)
		{
			AEMShipBase* AsShip = Cast<AEMShipBase>(ShipsInRectArray[i]);
			if (AsShip)
			{
				AsShip->SelectObject();
				SelectedShipsArray.AddUnique(AsShip);

				AEMPlayerController* Controller = Cast<AEMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				if (Controller)
				{
					Controller->ClearSelectedBuildings();
				}
			}

		}

		for (int i = 0; i < SelectedShipsArray.Num(); i++)
		{
			if (ShipsInRectArray.Find(SelectedShipsArray[i]) == -1)
			{
				AEMShipBase* AsShip = Cast<AEMShipBase>(SelectedShipsArray[i]);
				if (AsShip)
				{
					AsShip->DeselectObject();
					SelectedShipsArray.Remove(AsShip);
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

TArray<AEMShipBase*> AEMHeadUpDisplay::GetSelectedShips()
{
	return SelectedShipsArray;
}

void AEMHeadUpDisplay::CleanSelectedUnits()
{
	if (SelectedCharactersArray.Num() == 0) return;
	
	//UE_LOG(LogTemp, Warning, TEXT("CleanSelectedUnits Before - %d"), SelectedCharactersArray.Num());
	for (int i = 0; i < SelectedCharactersArray.Num(); i++)
	{
		auto Char = SelectedCharactersArray[i];
		if (Char)
		{
			Char->DeselectObject();
		}
		//SelectedCharactersArray.Remove(Char);
	}

	SelectedCharactersArray.Empty();
	//UE_LOG(LogTemp, Warning, TEXT("CleanSelectedUnits After - %d"), SelectedCharactersArray.Num());
}

void AEMHeadUpDisplay::AddUnit(AEMCharacterBase* InCharacter)
{
	InCharacter->SelectObject();
	SelectedCharactersArray.AddUnique(InCharacter);
}

