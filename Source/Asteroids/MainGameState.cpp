// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameState.h"
#include "Net/UnrealNetwork.h"

void AMainGameState::AddScore(int32 InScore)
{
	Score += InScore;
}

void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMainGameState, Score);
}