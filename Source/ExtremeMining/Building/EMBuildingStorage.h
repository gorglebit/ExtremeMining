// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EMBuildingBase.h"
#include "EMBuildingStorage.generated.h"

UCLASS()
class EXTREMEMINING_API AEMBuildingStorage : public AEMBuildingBase
{
	GENERATED_BODY()
private:
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Resourse")
		int32 Food;

	UPROPERTY(BlueprintReadOnly, Category = "Resourse")
		int32 Wood;

	UPROPERTY(BlueprintReadOnly, Category = "Resourse")
		int32 Money;

public:
//---------------------------
private:
protected:
	virtual void BeginPlay() override;
	void SetStorageWithDelay();
public:
	AEMBuildingStorage();

	FORCEINLINE int32 GetFoodAmount() { return Food; }
	FORCEINLINE int32 GetWoodAmount() { return Wood; }
	FORCEINLINE int32 GetMoneyAmount() { return Money; }

	void SetFoodAmount(const int32 Amount);
	void SetWoodAmount(const int32 Amount);
	void SetMoneyAmount(const int32 Amount);

};
