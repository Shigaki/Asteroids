// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidsPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.h"
#include "EndGameWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainGameMode.h"
#include "MainGameState.h"

void AAsteroidsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bVote = false;

	if (IsValid(EndGameWidgetClass))
	{
		EndGameWidget = Cast<UEndGameWidget>(CreateWidget(GetWorld(), EndGameWidgetClass));
	}
}

void AAsteroidsPlayerController::Client_PopUpEndGameUI_Implementation()
{
	if (EndGameWidget != nullptr)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			AMainGameState* MainGameState = Cast<AMainGameState>(World->GetGameState());
			MainGameState->HideScoreUI();
			EndGameWidget->UpdateFinalScoreText(MainGameState->Score);
			EndGameWidget->AddToViewport();
		}
	}
}

bool AAsteroidsPlayerController::VoteRestart()
{
	if (HasAuthority())
	{
		Server_VoteRestart();
	}
	else
	{
		Server_VoteRestart();
	}
	return true;
}

void AAsteroidsPlayerController::Server_VoteRestart_Implementation()
{
	UWorld* World = GetWorld();
	if (World)
	{
		AMainGameMode* MainGameMode = Cast<AMainGameMode>(World->GetAuthGameMode());
		MainGameMode->VoteRestartGame(this);
	}
}
