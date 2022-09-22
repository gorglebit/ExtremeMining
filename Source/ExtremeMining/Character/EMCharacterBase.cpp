// Fill out your copyright notice in the Description page of Project Settings.

#include "EMCharacterBase.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "../Building/EMBuildingBase.h"
#include "../Building/EMBuildingStorage.h"

//UE_LOG(LogTemp, Warning, TEXT(""));

AEMCharacterBase::AEMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	BodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMeshComponent->SetupAttachment(RootComponent);
	HatMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HatMesh"));
	HatMeshComponent->SetupAttachment(BodyMeshComponent);
	IsCommandActive = false;
	CharacterType = 0;
	WorkLocationRadius = 700;
	WorkLocationDelta = 500;

	CollectionRateNotWorker = 1;
	CollectionRateWorker = 5;

	GetCharacterMovement()->MaxWalkSpeed = 400;
}



void AEMCharacterBase::SetWorkLocation(const int32 BuildType)
{
	TSubclassOf<AEMBuildingBase> ActorClass;
	ActorClass = AEMBuildingBase::StaticClass();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingBase::StaticClass(), OutActors);

	for (int i = 0; i < OutActors.Num(); i++)
	{
		AEMBuildingBase* Building = Cast<AEMBuildingBase>(OutActors[i]);
		if (!Building) return;

		if (Building->GetBuildingType() == BuildType)
		{
			WorkLocation = Building->GetActorLocation() - FVector(WorkLocationDelta, 0, 0);
			return;
		}
	}
}

void AEMCharacterBase::CollectResouse()
{
	if (!BuildingStorage) return;

	if (CharacterType == CHARACTER_MAIN)
	{
		int rand = FMath::RandRange(1, 3);

		switch (rand)
		{
		case 1:
		{
			BuildingStorage->SetFoodAmount(BuildingStorage->GetFoodAmount() + CollectionRateNotWorker);
			break;
		}
		case 2:
		{
			BuildingStorage->SetWoodAmount(BuildingStorage->GetWoodAmount() + CollectionRateNotWorker);
			break;
		}
		case 3:
		{
			BuildingStorage->SetMoneyAmount(BuildingStorage->GetMoneyAmount() + CollectionRateNotWorker);
			break;
		}
		default:
			break;
		}
	}
	else 
	{
		switch (CharacterType)
		{
		case 1:
		{
			BuildingStorage->SetFoodAmount(BuildingStorage->GetFoodAmount() + CollectionRateWorker);
			break;
		}
		case 2:
		{
			BuildingStorage->SetWoodAmount(BuildingStorage->GetWoodAmount() + CollectionRateWorker);
			break;
		}
		case 3:
		{
			BuildingStorage->SetMoneyAmount(BuildingStorage->GetMoneyAmount() + CollectionRateWorker);
			break;
		}
		default:
			break;
		}
	}
}

void AEMCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	SetCharacterRole(CharacterType);
	SetWorkLocation(CharacterType);

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingStorage::StaticClass(), OutActors);
	BuildingStorage = Cast<AEMBuildingStorage>(OutActors[0]);
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
	BodyMeshComponent->SetRenderCustomDepth(true);
}

void AEMCharacterBase::DeselectObject()
{
	BodyMeshComponent->SetRenderCustomDepth(false);
}

void AEMCharacterBase::UnitMoveCommand(const FVector Location)
{
	IsCommandActive = true;
	GetCharacterMovement()->MaxWalkSpeed = 600;
	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(this);
	if (!AIController) return;

	AIController->StopMovement();
	AIController->MoveToLocation(Location, -1, true, true, false, true, nullptr, false);

	GetWorldTimerManager().SetTimer(TimerCheckMoveStatus, this, &AEMCharacterBase::CheckMoveStatus, 3.f, true);
}

void AEMCharacterBase::SetCharacterRole_Implementation(const int32 Type)
{
}

void AEMCharacterBase::CheckMoveStatus()
{
	//UE_LOG(LogTemp, Warning, TEXT("Timer start!!!"));
	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(this);
	if (!AIController) return;
	EPathFollowingStatus::Type Status = AIController->GetMoveStatus();

	if (Status == EPathFollowingStatus::Idle)
	{
		IsCommandActive = false;
		GetWorldTimerManager().ClearTimer(TimerCheckMoveStatus);
		GetCharacterMovement()->MaxWalkSpeed = 400;
		//UE_LOG(LogTemp, Warning, TEXT("Timer end!!!"));
	}
}