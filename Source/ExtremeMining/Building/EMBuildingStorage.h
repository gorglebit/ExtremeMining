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
	FORCEINLINE int32 GetFoodAmount() { return Food; }
	FORCEINLINE int32 GetWoodAmount() { return Wood; }
	FORCEINLINE int32 GetMoneyAmount() { return Money; }

	FORCEINLINE void SetFoodAmount(const int32 Amount) { Food = Amount; }
	FORCEINLINE void SetWoodAmount(const int32 Amount) { Wood = Amount; }
	FORCEINLINE void SetMoneyAmount(const int32 Amount) { Money = Amount; }
private:
protected:
	void BeginPlay() override;
public:
	AEMBuildingStorage();

};
