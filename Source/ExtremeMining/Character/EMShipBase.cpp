// Fill out your copyright notice in the Description page of Project Settings.

#include "../Character/EMShipBase.h"

#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

AEMShipBase::AEMShipBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMeshComponent->SetupAttachment(RootComponent);
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
	//GetCharacterMovement()->MaxWalkSpeed = 600;

	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(this);
	if (!AIController) return;

	UE_LOG(LogTemp, Warning, TEXT("Location x = %.f, y = $.f, z = %.f"), Location.X, Location.Y, Location.Z);

	AIController->StopMovement();
	AIController->MoveToLocation(Location, -1, true, true, false, true, nullptr, false);
}

