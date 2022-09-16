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
	AEMCameraPawn();

protected:
	virtual void BeginPlay() override;

	// Moving on tick near border
	UFUNCTION(BlueprintCallable)
		void MovePawnForwardBackTick();

	UFUNCTION(BlueprintCallable)
		void MovePawnRightLeftTick();
	//--------------
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;


	FVector2D ViewportSize;
	int32 CameraMoveSpeed;
	int32 CameraZoomSpeed;

	int32 TargetArmMaxLength;
	int32 TargetArmMinLength;

private:
	// Moving using keyboard
	void MovePawnForwardBackAxis(const float value);
	void MovePawnRightLeftAxis(const float value);
	//------------------

	//Camera zoom
	void CameraZoomIn();
	void CameraZoomOut();
	//----------------

	// Simple moving functions
	void MovePawnForward();
	void MovePawnBack();
	void MovePawnRight();
	void MovePawnLeft();
	//--------------------------
};
