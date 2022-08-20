// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Net/UnrealNetwork.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMainGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllerList.Add(NewPlayer);

}

void AMainGameMode::EndMatch()
{
	Super::EndMatch();

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, GetMatchState().ToString());
	// pause, show score, restart option, etc..
}

void AMainGameMode::EndMatchCheck()
{
	if (NumDeadPlayers == NumPlayers)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Players - Dead: %d, Total: %d"), NumDeadPlayers, NumPlayers));
		EndMatch();
	}
}

void AMainGameMode::IncrementNumDeadPlayers(bool bIncrement)
{
	bIncrement ? ++NumDeadPlayers : --NumDeadPlayers;
	EndMatchCheck();
}
