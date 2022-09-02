// Fill out your copyright notice in the Description page of Project Settings.


#include "General/EMCameraPawn.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AEMCameraPawn::AEMCameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Pawn settings
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom...
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComponent->SetupAttachment(RootComponent);

	SpringArmComponent->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	SpringArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArmComponent->TargetArmLength = 0.f;
	SpringArmComponent->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	SpringArmComponent->bEnableCameraLag = true;
	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	CameraMoveSpeed = 1400;
}

// Called when the game starts or when spawned
void AEMCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
}

// Called every frame
void AEMCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//MovePawnForwardNearBorder();
	MovePawnRightNearBorder();
}

// Called to bind functionality to input
void AEMCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEMCameraPawn::MovePawnForwardNearBorder()
{
	float mouseX, mouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);
	mouseY = FMath::Clamp(mouseY, 0, ViewportSize.Y);

	float delta = mouseY / ViewportSize.Y;

	if (delta > 0.95)
	{
		auto DeltaLocation = FVector::ZeroVector;
		DeltaLocation.X = CameraMoveSpeed * GetWorld()->GetDeltaSeconds() * -1;

		AddActorWorldOffset(DeltaLocation);
		UE_LOG(LogTemp, Warning, TEXT("%f > 95"), delta);
	}
	else
	{
		if (delta < 0.05)
		{
			UE_LOG(LogTemp, Warning, TEXT("%f < 0.05"), delta);
			auto DeltaLocation = FVector::ZeroVector;
			DeltaLocation.X = CameraMoveSpeed * GetWorld()->GetDeltaSeconds();

			AddActorWorldOffset(DeltaLocation);
		}
	}
}

void AEMCameraPawn::MovePawnRightNearBorder()
{
	float mouseX, mouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);
	mouseX = FMath::Clamp(mouseY, 0, ViewportSize.X);

	float delta = mouseX / ViewportSize.X;
	UE_LOG(LogTemp, Warning, TEXT("delta is - %f"), delta);
	if (delta > 0.95)
	{
		auto DeltaLocation = FVector::ZeroVector;
		DeltaLocation.Y = CameraMoveSpeed * GetWorld()->GetDeltaSeconds();

		AddActorWorldOffset(DeltaLocation);
		UE_LOG(LogTemp, Warning, TEXT("%f > 95"), delta);
	}
	else
	{
		if (delta < 0.05)
		{
			UE_LOG(LogTemp, Warning, TEXT("%f < 0.05"), delta);
			auto DeltaLocation = FVector::ZeroVector;
			DeltaLocation.Y = CameraMoveSpeed * GetWorld()->GetDeltaSeconds() * -1;

			AddActorWorldOffset(DeltaLocation);
		}
	}
}

