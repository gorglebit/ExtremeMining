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
	FVector2D ViewportSize;
	int32 CameraMoveSpeed;
	int32 CameraZoomSpeed;

	int32 TargetArmMaxLength;
	int32 TargetArmMinLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;
protected:
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
