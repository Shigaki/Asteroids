// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameState.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.h"
#include "EndGameWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainGameState::BeginPlay()
{
	Super::BeginPlay();

	Score = 0;

	if (IsValid(ScoreWidgetClass))
	{
		ScoreWidget = Cast<UScoreWidget>(CreateWidget(GetWorld(), ScoreWidgetClass));

		if (ScoreWidget != nullptr)
		{
			ScoreWidget->AddToViewport();
		}
	}

	if (IsValid(EndGameWidgetClass))
	{
		EndGameWidget = Cast<UEndGameWidget>(CreateWidget(GetWorld(), EndGameWidgetClass));
	}
}

void AMainGameState::UpdateScore(int32 InScore)
{
	Score += InScore;
	ScoreWidget->UpdateScoreText(Score);
}

void AMainGameState::PopUpEndGameUI_Implementation()
{
	if (EndGameWidget != nullptr)
	{
		ScoreWidget->RemoveFromViewport();

		EndGameWidget->UpdateFinalScoreText(Score);
		EndGameWidget->AddToViewport();

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}



void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMainGameState, Score);
}

