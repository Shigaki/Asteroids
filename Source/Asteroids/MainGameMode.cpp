// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "AsteroidsPlayerController.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (AAsteroidsPlayerController* PlayerController : PlayerControllerList)
	{
		FInputModeGameOnly InputModeData;
		PlayerController->SetInputMode(InputModeData);
		PlayerController->SetShowMouseCursor(false);
	}
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
		FInputModeUIOnly InputModeData;
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputModeData);
		PlayerController->SetShowMouseCursor(true);
	}
}

void AMainGameMode::VoteRestartGame(AAsteroidsPlayerController* InPlayer)
{
	if (!InPlayer->bVote)
	{
		InPlayer->bVote = true;
		++NumReadyPlayers;
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
		EndMatch();
	}
}

void AMainGameMode::IncrementNumDeadPlayers(bool bIncrement)
{
	bIncrement ? ++NumDeadPlayers : --NumDeadPlayers;
	EndMatchCheck();
}
