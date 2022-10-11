// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EMCameraPawn.generated.h"

UCLASS()
class EXTREMEMINING_API AEMCameraPawn : public APawn
{
	GENERATED_BODY()
private:
	FVector2D ScreenSize;
	int32 CameraMoveSpeed;
	int32 CameraZoomSpeed;

	int32 TargetArmMaxLength;
	int32 TargetArmMinLength;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class USpringArmComponent* SpringArmComponent;
public:
//------------------------------

private:
	void MovePawnForwardBackAxis(const float value);
	void MovePawnRightLeftAxis(const float value);

	void CameraZoomIn();
	void CameraZoomOut();

	void MovePawnForward();
	void MovePawnBack();
	void MovePawnRight();
	void MovePawnLeft();
	void SetScreenSize();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void MovePawnForwardBackTick();

	UFUNCTION(BlueprintCallable)
		void MovePawnRightLeftTick();
public:
	AEMCameraPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
