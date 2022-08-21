// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "AsteroidsPlayerController.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
}


void AMainGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllerList.Add(Cast<AAsteroidsPlayerController>(NewPlayer));
}

void AMainGameMode::EndMatch()
{
	Super::EndMatch();

	for (AAsteroidsPlayerController* PlayerController : PlayerControllerList)
	{
		PlayerController->Client_PopUpEndGameUI();
	}
}

void AMainGameMode::VoteRestartGame(AAsteroidsPlayerController* InPlayer)
{
	if (!InPlayer->bVote)
	{
		InPlayer->bVote = true;
		++NumReadyPlayers;
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Players Readt: %d"), NumReadyPlayers));
		if (NumReadyPlayers == NumPlayers)
		{
			RestartGame();
		}
	}
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
