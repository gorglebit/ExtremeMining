// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EMCameraPawn.generated.h"

UCLASS()
class EXTREMEMINING_API AEMCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEMCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;

	FVector2D ViewportSize;
	int32 CameraMoveSpeed;
	int32 CameraZoomSpeed;
private:
	// Moving on tick near border
	UFUNCTION()
		void MovePawnForwardBackTick();
	UFUNCTION()
		void MovePawnRightLeftTick();
	//--------------

	// Moving using keyboard
	UFUNCTION()
		void MovePawnForwardBackAxis(const float value);

	UFUNCTION()
		void MovePawnRightLeftAxis(const float value);
	//------------------

	//Camera zoom
	UFUNCTION()
		void CameraZoomIn();
	UFUNCTION()
		void CameraZoomOut();
	//----------------

	// Simple moving functions
	UFUNCTION()
		void MovePawnForward();
	UFUNCTION()
		void MovePawnBack();
	UFUNCTION()
		void MovePawnRight();
	UFUNCTION()
		void MovePawnLeft();
	//--------------------------
};
