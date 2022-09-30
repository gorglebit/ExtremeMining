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
	WorkLocationRadius = 700;
	WorkLocationDelta = 1100;

	CollectionRateNotWorker = 1;
	CollectionRateWorker = 5;

	FoodIntakeCount = 1;

	GetCharacterMovement()->MaxWalkSpeed = 400;
}



void AEMCharacterBase::SetWorkLocation(const int32 InCharacterType)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEMBuildingBase::StaticClass(), OutActors);

	if (InCharacterType == 0)
	{
		for (int i = 0; i < OutActors.Num(); i++)
		{
			AEMBuildingBase* AsBuilding = Cast<AEMBuildingBase>(OutActors[i]);
			if (AsBuilding->GetBuildingType() == 0) 
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

	int RandomNumber = 0;

	if (CharacterType == 0)
	{
		RandomNumber = FMath::RandRange(1, 3);

		switch (RandomNumber)
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

	SetCollectWidget(RandomNumber);
}

void AEMCharacterBase::SetMaxMoveSpeed(const int SpeedAmount)
{
	GetCharacterMovement()->MaxWalkSpeed = SpeedAmount;
}

void AEMCharacterBase::SetCollectWidget_Implementation(const int32 ResourceType)
{
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
	GetWorldTimerManager().SetTimer(CollectResourceTimer, this, &AEMCharacterBase::CollectResouse, 4.f, true);
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
	GetWorldTimerManager().PauseTimer(CollectResourceTimer);// CollectResourceTimer->

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
		GetWorldTimerManager().UnPauseTimer(CollectResourceTimer);
		//UE_LOG(LogTemp, Warning, TEXT("Timer end!!!"));
	}
}

void AEMCharacterBase::IntakeFood()
{
	StorageBuilding->SetFoodAmount(StorageBuilding->GetFoodAmount() - FoodIntakeCount);
}
