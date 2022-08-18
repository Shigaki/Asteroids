// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

bool AMainGameMode::ReadyToStartMatch_Implementation() 
{
	Super::ReadyToStartMatch();

	return MaxNumPlayers == NumPlayers;
}

void AMainGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllerList.Add(NewPlayer);
}
