// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "EMPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentCitizenCountChangedSignature, int32, NewAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxCitizenCountChangedSignature, int32, NewAmount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxResourceCountChangedSignature, int32, NewAmount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCitizenCountChangedSignature, int32, NewAmount);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCitizenFoodCountChangedSignature, int32, NewAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCitizenWoodCountChangedSignature, int32, NewAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCitizenMoneyCountChangedSignature, int32, NewAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCitizenNoneCountChangedSignature, int32, NewAmount);

UCLASS()
class EXTREMEMINING_API AEMPlayerState : public APlayerState
{
	GENERATED_BODY()
private:
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Citizen")
		int32 StartCitizenCount;

	UPROPERTY(BlueprintReadOnly, Category = "Citizen")
		int32 CurrentCitizenCount;

	UPROPERTY(BlueprintReadOnly, Category = "Citizen")
		int32 MaxCitizenCount;

	UPROPERTY(BlueprintReadOnly, Category = "Storage")
		int32 StartResourceCount;

	UPROPERTY(BlueprintReadOnly, Category = "Storage")
		int32 MaxResourceCount;

	UPROPERTY(BlueprintReadOnly, Category = "CitizenCount")
		int32 CitizenFoodCount;

	UPROPERTY(BlueprintReadOnly, Category = "Storage")
		int32 CitizenWoodCount;

	UPROPERTY(BlueprintReadOnly, Category = "Storage")
		int32 CitizenMoneyCount;

	UPROPERTY(BlueprintReadOnly, Category = "Storage")
		int32 CitizenNoneCount;
public:
	//FORCEINLINE int32 GetCitizenNoneCount() {return CitizenNoneCount}

	UPROPERTY(BlueprintAssignable)
		FOnCurrentCitizenCountChangedSignature OnCurrentCitizenCountChangedDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnMaxCitizenCountChangedSignature OnMaxCitizenCountChangedDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnMaxResourceCountChangedSignature OnMaxResourceCountChangedDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnCitizenCountChangedSignature OnCitizenCountChangedDelegate;
	//--------------------------------
	UPROPERTY(BlueprintAssignable)
		FOnCitizenNoneCountChangedSignature OnCitizenNoneCountChangedDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnCitizenFoodCountChangedSignature OnCitizenFoodCountChangedDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnCitizenWoodCountChangedSignature OnCitizenWoodCountChangedDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnCitizenMoneyCountChangedSignature OnCitizenMoneyCountChangedDelegate;
	

	//---------------------
private:
protected:
	virtual void BeginPlay() override;
public:
	AEMPlayerState();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetStartResourceCount() { return StartResourceCount; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetStartCitizenCount() { return StartCitizenCount; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetCurrentCitizenCount() { return CurrentCitizenCount; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void IncrementCurrentCitizenCount() { SetCurrentCitizenCount(CurrentCitizenCount + 1); }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetMaxCitizenCount() { return MaxCitizenCount; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE int32 GetMaxResourceCount() { return MaxResourceCount; }

	UFUNCTION(BlueprintCallable)
		void SetCurrentCitizenCount(const int32 InNewCount);

	UFUNCTION(BlueprintCallable)
		void SetMaxCitizenCount(const int32 InNewCount);

	UFUNCTION(BlueprintCallable)
		void SetMaxResourceCount(const int32 InNewCount);

	void IncrementCitizentCount(const int32 InCitizenType);
	void DecrementCitizentCount(const int32 InCitizenType);
};
 