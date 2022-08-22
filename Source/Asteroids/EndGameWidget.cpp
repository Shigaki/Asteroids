// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MainGameMode.h"
#include "AsteroidsPlayerController.h"

bool UEndGameWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (RetryButton)
	{
		RetryButton->OnClicked.AddDynamic(this, &ThisClass::RetryButtonClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &ThisClass::QuitButtonClicked);
	}

	return true;
}

void UEndGameWidget::UpdateFinalScoreText(int32 InScore)
{
	FinalScoreText->SetText(FText::FromString(FString::FromInt(InScore)));
}

void UEndGameWidget::RetryButtonClicked()
{
	RetryButton->SetIsEnabled(false);
	Cast<AAsteroidsPlayerController>(GetOwningPlayer())->Server_VoteRestart();
}


void UEndGameWidget::QuitButtonClicked()
{
	QuitButton->SetIsEnabled(false);
	GetOwningPlayer()->ClientTravel(MenuLevelPath, ETravelType::TRAVEL_Partial, false);
}

