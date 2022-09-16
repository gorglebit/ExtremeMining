// Fill out your copyright notice in the Description page of Project Settings.


#include "EMCameraPawn.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerController.h>

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
	SpringArmComponent->TargetArmLength = 3000.f;
	SpringArmComponent->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	SpringArmComponent->bEnableCameraLag = true;
	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	CameraMoveSpeed = 1000;
	CameraZoomSpeed = 100;
	TargetArmMaxLength = 4000;
	TargetArmMinLength = 1000;
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

	//MovePawnForwardBackTick();
	//MovePawnRightLeftTick();
}

// Called to bind functionality to input
void AEMCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("CameraPawnMoveForwardBack", this, &AEMCameraPawn::MovePawnForwardBackAxis);
	PlayerInputComponent->BindAxis("CameraPawnMoveRightLeft", this, &AEMCameraPawn::MovePawnRightLeftAxis);
	
	PlayerInputComponent->BindAction("CameraZoomIn",IE_Pressed, this, &AEMCameraPawn::CameraZoomIn);
	PlayerInputComponent->BindAction("CameraZoomOut",IE_Pressed, this, &AEMCameraPawn::CameraZoomOut);
}

void AEMCameraPawn::MovePawnForwardBackTick()
{
	float mouseX, mouseY;
	
	bool IsMouseEnable = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);
	if (!IsMouseEnable)
	{
		MovePawnBack();
		return;
	}

	float Ratio = mouseY / ViewportSize.Y;

	if (Ratio > 0.95)
		MovePawnForward();
	else
	{
		if (Ratio < 0.05)
			MovePawnBack();
	}
}

void AEMCameraPawn::MovePawnRightLeftTick()
{
	float mouseX, mouseY;
	
	bool IsMouseEnable = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);
	if (!IsMouseEnable) return;

	float Ratio = mouseX / ViewportSize.X;

	if (Ratio > 0.95)
		MovePawnRight();
	else
	{
		if (Ratio < 0.05)
			MovePawnLeft();
	}
}

void AEMCameraPawn::MovePawnForwardBackAxis(const float value)
{
	if (value == 0) return;

	if (value == 1)
	{
		MovePawnForward();
		return;
	}

	if (value == -1)
	{
		MovePawnBack();
		return;
	}
}

void AEMCameraPawn::MovePawnRightLeftAxis(const float value)
{
	if (value == 0) return;

	if (value == 1)
	{
		MovePawnRight();
		return;
	}

	if (value == -1)
	{
		MovePawnLeft();
		return;
	}
}

void AEMCameraPawn::CameraZoomIn()
{
	float NewArmLength = SpringArmComponent->TargetArmLength - CameraZoomSpeed;
	NewArmLength = FMath::Clamp(NewArmLength, TargetArmMinLength, TargetArmMaxLength);
	SpringArmComponent->TargetArmLength = NewArmLength;
	return;
}

void AEMCameraPawn::CameraZoomOut()
{
	float NewArmLength = SpringArmComponent->TargetArmLength + CameraZoomSpeed;
	NewArmLength = FMath::Clamp(NewArmLength, TargetArmMinLength, TargetArmMaxLength);
	SpringArmComponent->TargetArmLength = NewArmLength;
	return;
}

void AEMCameraPawn::MovePawnForward()
{
	if (!GetWorld()) return;

	auto DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = CameraMoveSpeed * GetWorld()->GetDeltaSeconds() * -1;

	AddActorWorldOffset(DeltaLocation);
}

void AEMCameraPawn::MovePawnBack()
{
	if (!GetWorld()) return;

	auto DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = CameraMoveSpeed * GetWorld()->GetDeltaSeconds();

	AddActorWorldOffset(DeltaLocation);
}

void AEMCameraPawn::MovePawnRight()
{
	if (!GetWorld()) return;

	auto DeltaLocation = FVector::ZeroVector;
	DeltaLocation.Y = CameraMoveSpeed * GetWorld()->GetDeltaSeconds();

	AddActorWorldOffset(DeltaLocation);
}

void AEMCameraPawn::MovePawnLeft()
{
	if (!GetWorld()) return;

	auto DeltaLocation = FVector::ZeroVector;
	DeltaLocation.Y = CameraMoveSpeed * GetWorld()->GetDeltaSeconds() * -1;

	AddActorWorldOffset(DeltaLocation);
}

