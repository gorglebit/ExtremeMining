// Fill out your copyright notice in the Description page of Project Settings.

#include "EMCharacterBase.h"

#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AEMCharacterBase::AEMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);
}

void AEMCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void AEMCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEMCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEMCharacterBase::SelectObject()
{
	BodyMesh->SetRenderCustomDepth(true);
}

void AEMCharacterBase::DeselectObject()
{
	BodyMesh->SetRenderCustomDepth(false);
}

void AEMCharacterBase::UnitMoveCommand(const FVector Location)
{
	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(this);
	if (!AIController) return;

	AIController->StopMovement();
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, Location);
}
