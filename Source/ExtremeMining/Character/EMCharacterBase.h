// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interface/EMBasicInterface.h"
#include "EMCharacterBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class EXTREMEMINING_API AEMCharacterBase : public ACharacter, public IEMBasicInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BodyMesh;
	
protected:
	UPROPERTY(BlueprintReadOnly)
		FVector WorkLocation;
	UPROPERTY(BlueprintReadWrite)
		int32 CharacterType;
	UPROPERTY(BlueprintReadWrite)
		bool IsCommandActive;

public:


private:
	void SetFirstWorkLocation();

private:

protected:
	virtual void BeginPlay() override;

public:
	AEMCharacterBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SelectObject() override;

	virtual void DeselectObject() override;

	virtual void UnitMoveCommand(const FVector Location) override;


};
