// Fill out your copyright notice in the Description page of Project Settings.

#include "../Character/EMShipBase.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "../Character/EMCharacterBase.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

AEMShipBase::AEMShipBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMeshComponent->SetupAttachment(RootComponent);
	
	FirstSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FirstSceneComponent"));
	FirstSceneComponent->SetupAttachment(BodyMeshComponent);
	FirstSceneComponent->SetRelativeLocation(FVector(-250, 0, -100));

	SecondSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SecondSceneComponent"));
	SecondSceneComponent->SetupAttachment(BodyMeshComponent);
	SecondSceneComponent->SetRelativeLocation(FVector(50, 0, -100));

	ThirdSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ThirdSceneComponent"));
	ThirdSceneComponent->SetupAttachment(BodyMeshComponent);
	ThirdSceneComponent->SetRelativeLocation(FVector(-80, 0, 365));

	CurrentNumberOfPassangers = 0;
	MaxNumberOfPassangers = 3;

	GetCharacterMovement()->MaxWalkSpeed = 200;
}

void AEMShipBase::BeginPlay()
{
	Super::BeginPlay();
	
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
		SetSailVisual();
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
	UE_LOG(LogTemp, Warning, TEXT("InScene"));

	InPassenger->SetActorLocation(InScene->GetComponentLocation());
	InPassenger->AttachToComponent(InScene, FAttachmentTransformRules::KeepWorldTransform);

	InPassenger->SetCollectionResource(false);
	InPassenger->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	
	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(InPassenger);
	if (!AIController) return;
	AIController->GetBrainComponent()->StopLogic(FString());

	PassengersOnBoardArray.AddUnique(InPassenger);
	CurrentNumberOfPassangers++;
	UE_LOG(LogTemp, Warning, TEXT("CurrentNumberOfPassangers++"));
}

void AEMShipBase::SetSailVisual_Implementation()
{
}
