// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../Interface/EMBasicInterface.h"
#include "EMCharacterBase.generated.h"

UCLASS()
class EXTREMEMINING_API AEMCharacterBase : public ACharacter, public IEMBasicInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BodyMesh;

public:
	AEMCharacterBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
		void UnitMoveCommandBP(const FVector Location);

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SelectObject() override;

	virtual void DeselectObject() override;

	virtual void UnitMoveCommand(const FVector Location) override;


};
