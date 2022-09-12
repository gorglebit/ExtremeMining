// Fill out your copyright notice in the Description page of Project Settings.


#include "EMCharacterBase.h"

// Sets default values
AEMCharacterBase::AEMCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEMCharacterBase::ShowThatDeselected_Implementation()
{
}

// Called every frame
void AEMCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEMCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEMCharacterBase::SelectObject()
{
	ShowThatSelected();
}

void AEMCharacterBase::DeselectObject()
{
	ShowThatDeselected();
}

void AEMCharacterBase::ShowThatSelected_Implementation()
{
}
