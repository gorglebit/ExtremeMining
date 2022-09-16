// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/EMBasicInterface.h"
#include "EMBuildingBase.generated.h"

UCLASS()
class EXTREMEMINING_API AEMBuildingBase : public AActor, public IEMBasicInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BuildMesh;

public:	
	AEMBuildingBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SelectObject() override;

	virtual void DeselectObject() override;

};
