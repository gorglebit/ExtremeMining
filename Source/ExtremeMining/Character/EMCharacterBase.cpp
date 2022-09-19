// Fill out your copyright notice in the Description page of Project Settings.

#include "EMCharacterBase.h"

#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "..\Building\EMBuildingBase.h"
#include "Tasks/AITask_MoveTo.h"
#include "Navigation/PathFollowingComponent.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

AEMCharacterBase::AEMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);

	IsCommandActive = false;
	CharacterType = 0;
}



void AEMCharacterBase::SetFirstWorkLocation()
{
	TSubclassOf<AEMBuildingBase> ActorClass;
	ActorClass = AEMBuildingBase::StaticClass();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingBase::StaticClass(), OutActors);

	for (int i = 0; i < OutActors.Num(); i++)
	{
		AEMBuildingBase* Building = Cast<AEMBuildingBase>(OutActors[i]);
		if (!Building) return;

		if (Building->BuildingType == BuildingType::BUILDING_MAIN)
		{
			WorkLocation = Building->GetActorLocation() - FVector(900, 0, 0);
			return;
		}
	}
}

void AEMCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	SetFirstWorkLocation();
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
	IsCommandActive = true;
	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(this);
	if (!AIController) return;

	AIController->StopMovement();
	AIController->MoveToLocation(Location, -1, true, true, false, true, nullptr, false);

	TimerCheckMoveStatus;
	GetWorldTimerManager().SetTimer(TimerCheckMoveStatus, this, &AEMCharacterBase::CheckMoveStatus, 3.f, true);
}

void AEMCharacterBase::CheckMoveStatus()
{
	UE_LOG(LogTemp, Warning, TEXT("Timer start!!!"));
	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(this);
	if (!AIController) return;
	EPathFollowingStatus::Type Status = AIController->GetMoveStatus();

	if (Status == EPathFollowingStatus::Idle)
	{
		IsCommandActive = false;
		GetWorldTimerManager().ClearTimer(TimerCheckMoveStatus);
		UE_LOG(LogTemp, Warning, TEXT("Timer end!!!"));
	}
}