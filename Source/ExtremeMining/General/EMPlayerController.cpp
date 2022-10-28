// Fill out your copyright notice in the Description page of Project Settings.

#include "EMPlayerController.h"
#include "GameFramework/HUD.h"
#include "Components/BoxComponent.h"

#include "../General/EMHeadUpDisplay.h"
#include "../Building/EMBuildingBase.h"
#include "../Character/EMCharacterBase.h"
#include "../Character/EMShipBase.h"
#include "../Core/EMCoreActor.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

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

	//UE_LOG(LogTemp, Warning, TEXT("GrabSelectedUnits - %d"), HUD->GrabSelectedUnits().Num());
}

void AEMPlayerController::SelectObjectStartAction()
{
	AEMHeadUpDisplay* HUD = Cast<AEMHeadUpDisplay>(GetHUD());
	if (!HUD) return;
	
	//UE_LOG(LogTemp, Warning, TEXT(""));

	HUD->CleanSelectedUnits();
	ClearSelectedBuildings();

	FHitResult Hit;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery_MAX, true, Hit);
	
	AEMBuildingBase* AsBuilding = Cast<AEMBuildingBase>(Hit.GetActor());
	if (AsBuilding)
	{
		AsBuilding->SelectObject();
		SelectedBuilding = AsBuilding;
		return;
	}

	AEMCharacterBase* AsCharacter = Cast<AEMCharacterBase>(Hit.GetActor());
	if (AsCharacter)
	{
		AsCharacter->SelectObject();
		HUD->AddCitizen(AsCharacter);
		return;
	}

	AEMShipBase* AsShip = Cast<AEMShipBase>(Hit.GetActor());
	if (AsShip)
	{
		AsShip->SelectObject();
		SelectedShip = AsShip;
		HUD->AddShip(AsShip);
		return;
	}

	IsLeftMousePressed = true;
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
	// Hit
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery_MAX, true, HitResult);
	
	//If Hit is a Building
	AEMBuildingBase* AsBuilding = Cast<AEMBuildingBase>(HitResult.GetActor());
	
	if (AsBuilding)
	{
		RightMouseLocation = AsBuilding->GetBoxComponent()->GetComponentLocation();
	}
	else
	{
		RightMouseLocation = HitResult.Location;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Location - x = %f, y = %f, z = %f ,"), RightMouseLocation.X, RightMouseLocation.Y, RightMouseLocation.Z);
	//-----------------

	//Take selected units
	AEMHeadUpDisplay* HUD = Cast<AEMHeadUpDisplay>(GetHUD());
	if (!HUD) return;
	TArray<AEMCharacterBase*> SelectedCharactersArray = HUD->GrabSelectedUnits();
	
	// Selected units move
	for (int i = 0; i < SelectedCharactersArray.Num(); i++)
	{
		// RightMouseLocation or other formation location
		if (SelectedCharactersArray[i])
		{
			SelectedCharactersArray[i]->UnitMoveCommand(RightMouseLocation);
		}	
	}
	//--------------------------
	TArray<AEMShipBase*> SelectedShipsArray = HUD->GetSelectedShips();

	// Selected Ship move
	for (int i = 0; i < SelectedShipsArray.Num(); i++)
	{
		// RightMouseLocation or other formation location
		if (SelectedShipsArray[i])
		{
			SelectedShipsArray[i]->UnitMoveCommand(RightMouseLocation);
			//UE_LOG(LogTemp, Warning, TEXT("UnitMoveCommand"));
		}
	}
	//--------------------------

	//If hit is Ship
	AEMShipBase* AsShip = Cast<AEMShipBase>(HitResult.GetActor());

	if (AsShip)
	{
		for (int i = 0; i < SelectedCharactersArray.Num(); i++)
		{
			// RightMouseLocation or other formation location
			auto AsCharacter = SelectedCharactersArray[i];
			if (AsCharacter)
			{
				float Distance = AEMCoreActor::GetDistance(AsShip, AsCharacter);
				//UE_LOG(LogTemp, Warning, TEXT("Distance - %f"), Distance);
				if (Distance < 1000 && AsCharacter->GetCharacterType() == 4)
				{
					AsShip->TakePassengerOnBoard(AsCharacter);
					//UE_LOG(LogTemp, Warning, TEXT("SelectedCharactersArray - %d"), SelectedCharactersArray.Num());
				}
				//SelectedCharactersArray[i]->UnitMoveCommand(RightMouseLocation);
			}
		}
	}
	//-------------
}

void AEMPlayerController::ConnonVolleyRightAction()
{
	//UE_LOG(LogTemp, Warning, TEXT("ConnonVolleyRightAction"));

	AEMHeadUpDisplay* HUD = Cast<AEMHeadUpDisplay>(GetHUD());
	if (!HUD) return;
	if (HUD->GetSelectedShips().Num() != 1) return;
	if (!SelectedShip) return;

	SelectedShip->CannonsVolleyAttack(true);
}

void AEMPlayerController::ConnonVolleyLeftAction()
{
	AEMHeadUpDisplay* HUD = Cast<AEMHeadUpDisplay>(GetHUD());
	if (!HUD) return;
	if (HUD->GetSelectedShips().Num() != 1) return;
	if (!SelectedShip) return;
	UE_LOG(LogTemp, Warning, TEXT("LEFT"));
	SelectedShip->CannonsVolleyAttack(false);
}

void AEMPlayerController::ClearSelectedBuildings()
{
	if (SelectedBuilding)
	{
		SelectedBuilding->DeselectObject();
		SelectedBuilding = NULL;
	}
}

void AEMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SelectObject", IE_Pressed, this, &AEMPlayerController::SelectObjectStartAction);
	InputComponent->BindAction("SelectObject", IE_Released, this, &AEMPlayerController::SelectObjectStopAction);
	InputComponent->BindAction("MoveToLocation", IE_Released, this, &AEMPlayerController::MoveToLocationAction);
	
	InputComponent->BindAction("CannonsVolleyRight", IE_Released, this, &AEMPlayerController::ConnonVolleyRightAction);
	InputComponent->BindAction("CannonsVolleyLeft", IE_Released, this, &AEMPlayerController::ConnonVolleyLeftAction);

}


