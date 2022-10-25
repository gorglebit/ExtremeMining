// Fill out your copyright notice in the Description page of Project Settings.

#include "../Character/EMShipBase.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Button.h"

#include "../UserInterface/EMShipWidget.h"
#include "../Character/EMCharacterBase.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

AEMShipBase::AEMShipBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMeshComponent->SetupAttachment(RootComponent);
	BodyMeshComponent->SetRelativeLocation(FVector(0, 0, 500));

	FirstSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FirstSceneComponent"));
	FirstSceneComponent->SetupAttachment(BodyMeshComponent);
	FirstSceneComponent->SetRelativeLocation(FVector(-250, 0, -100));

	SecondSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SecondSceneComponent"));
	SecondSceneComponent->SetupAttachment(BodyMeshComponent);
	SecondSceneComponent->SetRelativeLocation(FVector(300, 0, -100));

	ThirdSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ThirdSceneComponent"));
	ThirdSceneComponent->SetupAttachment(BodyMeshComponent);
	ThirdSceneComponent->SetRelativeLocation(FVector(-80, 0, 365));

	ShipWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BuildingWidget"));
	ShipWidget->SetupAttachment(BodyMeshComponent);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	CurrentNumberOfPassangers = 0;
	MaxNumberOfPassangers = 3;
	IsButtonVisible = false;
	IsCanDropped = true;

	ShipWidget->SetVisibility(IsButtonVisible);

	GetCharacterMovement()->MaxWalkSpeed = 200;
}

void AEMShipBase::OnDropOffPassangers()
{
	//UE_LOG(LogTemp, Warning, TEXT("OnDropOffPassangers"));

	if (!IsCanDropped) return;

	IsCanDropped = false;

	FTimerHandle IsDroppedTimer;
	GetWorld()->GetTimerManager().SetTimer(IsDroppedTimer, [this]()
		{
			IsCanDropped = true;
		}
	, 1.f, false);

	for (int i = CurrentNumberOfPassangers; i > 0; i--)
	{
		auto Passenger = PassengersOnBoardArray[i - 1];
		GetOffPassengerFromBoard(Passenger);
	}
}

void AEMShipBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(CheckLandTimer, this, &AEMShipBase::SetGetOffButtonTimer, 0.5f, true);

	auto AsUserWidget = Cast<UEMShipWidget>(ShipWidget->GetWidget());
	if (!AsUserWidget) return;
	AsUserWidget->GetGetOffButton()->OnClicked.AddDynamic(this, &AEMShipBase::OnDropOffPassangers);
}

void AEMShipBase::SetGetOffButtonTimer()
{
	SetLandButtonVisibitity();

	//UE_LOG(LogTemp, Warning, TEXT("SpawnPassengersLocation - x = %f, y = %f, z = %f ,"), SpawnPassengersLocation.X, SpawnPassengersLocation.Y, SpawnPassengersLocation.Z);

	auto AsUserWidget = Cast<UEMShipWidget>(ShipWidget->GetWidget());
	if (!AsUserWidget) return;

	if (IsButtonVisible)
	{
		if (CurrentNumberOfPassangers == 0)
		{
			ShipWidget->SetVisibility(false);
			AsUserWidget->GetGetOffButton()->SetIsEnabled(false);
		}
		else
		{
			ShipWidget->SetVisibility(true);
			AsUserWidget->GetGetOffButton()->SetIsEnabled(true);
			//AsUserWidget->GetGetOffButton()->OnClicked.AddDynamic(this, &AEMShipBase::OnDropOffPassangers);
		}
	}
	else
	{
		ShipWidget->SetVisibility(false);
		AsUserWidget->GetGetOffButton()->SetIsEnabled(false);
		//AsUserWidget->GetGetOffButton()->OnClicked.RemoveDynamic(this, &AEMShipBase::OnDropOffPassangers);
	}
}

void AEMShipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEMShipBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEMShipBase::SelectObject()
{
	BodyMeshComponent->SetRenderCustomDepth(true);
}

void AEMShipBase::DeselectObject()
{
	BodyMeshComponent->SetRenderCustomDepth(false);
}

void AEMShipBase::UnitMoveCommand(const FVector Location)
{
	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(this);
	if (!AIController) return;

	UE_LOG(LogTemp, Warning, TEXT("Location x = %.f, y = $.f, z = %.f"), Location.X, Location.Y, Location.Z);

	AIController->StopMovement();
	AIController->MoveToLocation(Location, -1, true, true, false, true, nullptr, false);
}

void AEMShipBase::TakePassengerOnBoard(AEMCharacterBase* InPassenger)
{
	switch (CurrentNumberOfPassangers)
	{
	case 0:
	{
		SeatPassengerOnPlace(InPassenger, FirstSceneComponent);
		break;
	}
	case 1:
	{
		SeatPassengerOnPlace(InPassenger, SecondSceneComponent);
		break;
	}
	case 2:
	{
		SeatPassengerOnPlace(InPassenger, ThirdSceneComponent);

		GetCharacterMovement()->MaxWalkSpeed = 1000;
		SetSailVisual(true);
		break;
	}
	default:
		break;
	}
}

void AEMShipBase::GetOffPassengerFromBoard(AEMCharacterBase* InPassenger)
{
	switch (CurrentNumberOfPassangers)
	{
	case 1:
	{
		GetOffPassengerFromPlace(InPassenger, FirstSceneComponent);

		GetCharacterMovement()->MaxWalkSpeed = 200;
		SetSailVisual(false);
		break;
	}
	case 2:
	{
		GetOffPassengerFromPlace(InPassenger, SecondSceneComponent);
		break;
	}
	case 3:
	{
		GetOffPassengerFromPlace(InPassenger, ThirdSceneComponent);
		break;
	}
	default:
		break;
	}
}

void AEMShipBase::SeatPassengerOnPlace(AEMCharacterBase* InPassenger, USceneComponent* InScene)
{
	if (!InPassenger) return;
	if (!InScene) return;

	InPassenger->SetActorLocation(InScene->GetComponentLocation());
	InPassenger->AttachToComponent(InScene, FAttachmentTransformRules::KeepWorldTransform);

	InPassenger->SetCollectionResource(false);
	InPassenger->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(InPassenger);
	if (!AIController) return;
	AIController->GetBrainComponent()->StopLogic(FString());

	PassengersOnBoardArray.AddUnique(InPassenger);
	CurrentNumberOfPassangers++;
	//UE_LOG(LogTemp, Warning, TEXT("CurrentNumberOfPassangers++"));
}

void AEMShipBase::GetOffPassengerFromPlace(AEMCharacterBase* InPassenger, USceneComponent* InScene)
{
	if (!InPassenger) return;
	if (!InScene) return;

	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(InPassenger);
	if (!AIController) return;

	AIController->GetBrainComponent()->StartLogic();
	
	InPassenger->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	InPassenger->SetCollectionResource(true);

	InPassenger->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	bool b = InPassenger->SetActorLocation(SpawnPassengersLocation, false, 0, ETeleportType::None);
	UE_LOG(LogTemp, Warning, TEXT("SetActorLocation - %d"), b);

	PassengersOnBoardArray.Remove(InPassenger);
	CurrentNumberOfPassangers--;

	SpawnPassengersLocation.Z += 400;
}

void AEMShipBase::SetSailVisual_Implementation(const bool IsVisible)
{
}

void AEMShipBase::SetLandButtonVisibitity_Implementation()
{
}