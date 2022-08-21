// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Asteroids/MainGameState.h"

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
	UWorld* World = GetWorld();
	if (World)
	{
		AMainGameState* MainGameState = Cast<AMainGameState>(World->GetGameState());
		MainGameState->PopUpEndGameUI();
	}
	//UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMainGameMode::PlayerReady()
{
	++NumReadyPlayers;
	if (NumReadyPlayers == NumPlayers)
	{
		RestartGame();
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
