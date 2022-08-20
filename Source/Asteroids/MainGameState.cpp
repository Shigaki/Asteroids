// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameState.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.h"

void AMainGameState::BeginPlay()
{
	Super::BeginPlay();

	Score = 0;

	if (IsValid(WidgetClass))
	{
		ScoreWidget = Cast<UScoreWidget>(CreateWidget(GetWorld(), WidgetClass));

		if (ScoreWidget != nullptr)
		{
			ScoreWidget->AddToViewport();
		}
	}
}

void AMainGameState::UpdateScore(int32 InScore)
{
	Score += InScore;
	ScoreWidget->UpdateScoreText(Score);
}

void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMainGameState, Score);
}
