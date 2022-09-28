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
	IsHungry = false;
	CharacterType = 0;
	WorkLocationRadius = 1000;
	WorkLocationDelta = 0;

	CollectionRateNotWorker = 1;
	CollectionRateWorker = 7;

	FoodIntakeCount = 1;

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
	if (!StorageBuilding) return;
	//UE_LOG(LogTemp, Warning, TEXT("StorageBuilding = true"));

	if (CharacterType == 0)
	{
		int rand = FMath::RandRange(1, 3);

		switch (rand)
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
			StorageBuilding->SetFoodAmount(StorageBuilding->GetFoodAmount() + CollectionRateWorker);
			break;
		}
		case 2:
		{
			StorageBuilding->SetWoodAmount(StorageBuilding->GetWoodAmount() + CollectionRateWorker);
			break;
		}
		case 3:
		{
			StorageBuilding->SetMoneyAmount(StorageBuilding->GetMoneyAmount() + CollectionRateWorker);
			break;
		}
		default:
			break;
		}
	}
}

void AEMCharacterBase::SetMaxMoveSpeed(const int SpeedAmount)
{
	GetCharacterMovement()->MaxWalkSpeed = SpeedAmount;
}

void AEMCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	SetCharacterRole(CharacterType);
	SetWorkLocation(CharacterType);

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingStorage::StaticClass(), OutActors);
	StorageBuilding = Cast<AEMBuildingStorage>(OutActors[0]);

	GetWorldTimerManager().SetTimer(FoodIntakeTimer, this, &AEMCharacterBase::IntakeFood, 2.5f, true);
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
	IsCommandActive = true;
	GetCharacterMovement()->MaxWalkSpeed = 600;
	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(this);
	if (!AIController) return;

	AIController->StopMovement();
	AIController->MoveToLocation(Location, -1, true, true, false, true, nullptr, false);

	GetWorldTimerManager().SetTimer(CheckMoveStatusTimer, this, &AEMCharacterBase::CheckMoveStatus, 3.f, true);
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
		//UE_LOG(LogTemp, Warning, TEXT("Timer end!!!"));
	}
}

void AEMCharacterBase::IntakeFood()
{
	StorageBuilding->SetFoodAmount(StorageBuilding->GetFoodAmount() - FoodIntakeCount);
}
