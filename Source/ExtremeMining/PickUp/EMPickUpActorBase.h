// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "EMPickUpActorBase.generated.h"

UCLASS()
class EXTREMEMINING_API AEMPickUpActorBase : public AStaticMeshActor
{
	GENERATED_BODY()
private:
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 ResourceType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 ResourceCount;
public:
//--------------------------
private:
	FTimerHandle DestroyTimerHandle;
protected:
	virtual void BeginPlay() override;

	int32 SetRandomType();
	int32 SetRandomCount();

	UFUNCTION(BlueprintNativeEvent)
		void SetTypeVisual(const int32 InResourceType);

public:
	AEMPickUpActorBase();

	void DestroyActorAfterGrab();

	FORCEINLINE int32 GetResourceType() { return ResourceType; }
	FORCEINLINE int32 GetResourceCount() { return ResourceCount; }
	
	
};
