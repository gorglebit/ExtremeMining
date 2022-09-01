// Fill out your copyright notice in the Description page of Project Settings.


#include "General/EMPawn.h"

// Sets default values
AEMPawn::AEMPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEMPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEMPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEMPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

