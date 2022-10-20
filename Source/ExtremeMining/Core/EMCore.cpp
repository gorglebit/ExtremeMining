// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/EMCore.h"

EMCore::EMCore()
{
}

EMCore::~EMCore()
{
}

float EMCore::GetDistance(AActor* InActorFrom, AActor* InActorTo)
{
	return (InActorFrom->GetActorLocation() - InActorTo->GetActorLocation()).Size();
}
