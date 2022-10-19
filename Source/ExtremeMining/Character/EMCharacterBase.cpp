// Fill out your copyright notice in the Description page of Project Settings.

#include "EMCharacterBase.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

#include "../Core/EMCore.h"
#include "../General/EMPlayerState.h"
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
	IsHungry = false;
	CharacterType = 0;
	WorkLocationRadius = 1400;
	WorkLocationDelta = 1400;

	CollectionRateNotWorker = 1;

	CollectionRateWorkerStart = 5;

	CollectionRateWorkerFood = CollectionRateWorkerStart;
	CollectionRateWorkerWood = CollectionRateWorkerStart;
	CollectionRateWorkerMoney = CollectionRateWorkerStart;

	CollectionRateWorkerDelta = 2;
	FinesIfHungry = 0;

	FoodIntakeCount = 1;

	GetCharacterMovement()->MaxWalkSpeed = 400;
}

void AEMCharacterBase::SetWorkLocation(const int32 InCharacterType)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingBase::StaticClass(), OutActors);

	if (InCharacterType == CHARACTER_TYPE_CITIZEN)
	{
		for (int i = 0; i < OutActors.Num(); i++)
		{
			AEMBuildingBase* AsBuilding = Cast<AEMBuildingBase>(OutActors[i]);
			if (AsBuilding->GetBuildingType() == BUILDING_TYPE_MAIN)
			{
				WorkLocation = AsBuilding->GetActorLocation() - FVector(WorkLocationDelta, 0, 0);
				return;
			}
		}
	}
	else
	{
		for (int i = 0; i < OutActors.Num(); i++)
		{
			AEMBuildingBase* AsBuilding = Cast<AEMBuildingBase>(OutActors[i]);
			if (AsBuilding->GetBuildingType() == InCharacterType)
			{
				WorkLocation = AsBuilding->GetActorLocation();
				return;
			}
		}
	}
}

void AEMCharacterBase::CollectResouse()
{
	if (!StorageBuilding) return;
	//UE_LOG(LogTemp, Warning, TEXT("StorageBuilding = true"));

	int ResourseType = 0;

	if (CharacterType == CHARACTER_TYPE_CITIZEN)
	{
		ResourseType = FMath::RandRange(1, 3);

		switch (ResourseType)
		{
		case 1:
		{
			StorageBuilding->SetFoodAmount(StorageBuilding->GetFoodAmount() + CollectionRateNotWorker);
			break;
		}
		case 2:
		{
			StorageBuilding->SetWoodAmount(StorageBuilding->GetWoodAmount() + CollectionRateNotWorker);
			break;
		}
		case 3:
		{
			StorageBuilding->SetMoneyAmount(StorageBuilding->GetMoneyAmount() + CollectionRateNotWorker);
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
			CollectionRateWorkerFood = CollectionRateWorkerStart + (GetBuildingLevel(BUILDING_TYPE_FOOD) * CollectionRateWorkerDelta) - FinesIfHungry;
			StorageBuilding->SetFoodAmount(StorageBuilding->GetFoodAmount() + CollectionRateWorkerFood);
			break;
		}
		case 2:
		{
			CollectionRateWorkerWood = CollectionRateWorkerStart + (GetBuildingLevel(BUILDING_TYPE_WOOD) * CollectionRateWorkerDelta) - FinesIfHungry;
			StorageBuilding->SetWoodAmount(StorageBuilding->GetWoodAmount() + CollectionRateWorkerWood);
			break;
		}
		case 3:
		{
			CollectionRateWorkerMoney = CollectionRateWorkerStart + (GetBuildingLevel(BUILDING_TYPE_MONEY) * CollectionRateWorkerDelta) - FinesIfHungry;
			StorageBuilding->SetMoneyAmount(StorageBuilding->GetMoneyAmount() + CollectionRateWorkerMoney);
			break;
		}
		default:
			break;
		}
	}

	SetCollectWidget(ResourseType);
}

int32 AEMCharacterBase::GetBuildingLevel(const int32 BuildingType)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingBase::StaticClass(), OutActors);

	int32 BuildLevel = 0;
	for (int i = 0; i < OutActors.Num(); i++)
	{
		auto AsBuilding = Cast<AEMBuildingBase>(OutActors[i]);
		if (AsBuilding->GetBuildingType() == BuildingType)
		{
			BuildLevel = AsBuilding->GetBuildingLevel();
		}
	}
	return BuildLevel;
}

void AEMCharacterBase::SetMaxMoveSpeed(const int SpeedAmount)
{
	GetCharacterMovement()->MaxWalkSpeed = SpeedAmount;
}

void AEMCharacterBase::SpawnMoveCommandFX_Implementation()
{
}

void AEMCharacterBase::SetCollectWidget_Implementation(const int32 ResourceType)
{
}

void AEMCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	SetCharacterType(0);
	SetCharacterRole(CharacterType);
	SetWorkLocation(CharacterType);

	SetStorageLocation();

	GetWorldTimerManager().SetTimer(FoodIntakeTimer, this, &AEMCharacterBase::IntakeFood, 2.5f, true);
	GetWorldTimerManager().SetTimer(CollectResourceTimer, this, &AEMCharacterBase::CollectResouse, 4.f, true);


}

void AEMCharacterBase::SetStorageLocation()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingStorage::StaticClass(), OutActors);
	StorageBuilding = Cast<AEMBuildingStorage>(OutActors[0]);
	if (!StorageBuilding) return;
	StorageLocation = StorageBuilding->GetBoxComponent()->GetComponentLocation();

	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!AsState) return;

	AsState->IncrementCitizentCount(CharacterType);
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
	HatMeshComponent->SetRenderCustomDepth(true);
}

void AEMCharacterBase::DeselectObject()
{
	BodyMeshComponent->SetRenderCustomDepth(false);
	HatMeshComponent->SetRenderCustomDepth(false);
}

void AEMCharacterBase::UnitMoveCommand(const FVector Location)
{
	SpawnMoveCommandFX();

	IsCommandActive = true;
	GetCharacterMovement()->MaxWalkSpeed = 600;
	GetWorldTimerManager().PauseTimer(CollectResourceTimer);// CollectResourceTimer->

	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(this);
	if (!AIController) return;

	AIController->StopMovement();
	AIController->MoveToLocation(Location, -1, true, true, false, true, nullptr, false);

	GetWorldTimerManager().SetTimer(CheckMoveStatusTimer, this, &AEMCharacterBase::CheckMoveStatus, 3.f, true);
}

void AEMCharacterBase::SetIsHungry(const bool InCondition)
{
	IsHungry = InCondition;

	if (InCondition)
		FinesIfHungry = 2;
	else
		FinesIfHungry = 0;
}

void AEMCharacterBase::SetCharacterType(const int32 InCharType)
{
	auto AsState = Cast<AEMPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (!AsState) return;
	
	if (CharacterType == InCharType) return;

	if (CharacterType != InCharType)
	{
		AsState->DecrementCitizentCount(CharacterType);
		
		CharacterType = InCharType;

		AsState->IncrementCitizentCount(InCharType);
		return;
	}
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
		GetWorldTimerManager().ClearTimer(CheckMoveStatusTimer);
		GetCharacterMovement()->MaxWalkSpeed = 400;
		GetWorldTimerManager().UnPauseTimer(CollectResourceTimer);
		//UE_LOG(LogTemp, Warning, TEXT("Timer end!!!"));
	}
}

void AEMCharacterBase::IntakeFood()
{
	StorageBuilding->SetFoodAmount(StorageBuilding->GetFoodAmount() - FoodIntakeCount);
}
