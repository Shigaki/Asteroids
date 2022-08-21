// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MainGameMode.h"

bool UEndGameWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (RetryButton && GetOwningPlayerPawn()->IsNetMode(ENetMode::NM_ListenServer))
	{
		RetryButton->OnClicked.AddDynamic(this, &ThisClass::RetryButtonClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &ThisClass::QuitButtonClicked);
	}

	if (GetOwningPlayerPawn()->IsNetMode(ENetMode::NM_Client))
	{
		RetryButton->RemoveFromParent();
	}

	return true;
}

void UEndGameWidget::UpdateFinalScoreText(int32 InScore)
{
	FinalScoreText->SetText(FText::FromString(FString::FromInt(InScore)));
}

void UEndGameWidget::RetryButtonClicked()
{
	UWorld* World = GetWorld();
	if (World)
	{
		AMainGameMode* MainGameMode = Cast<AMainGameMode>(World->GetAuthGameMode());
		MainGameMode->RestartGame();
	}
}

void UEndGameWidget::QuitButtonClicked()
{
	if (GetOwningPlayerPawn()->IsNetMode(ENetMode::NM_Client))
	{
		GetOwningPlayer()->ClientTravel(MenuLevelPath, ETravelType::TRAVEL_Absolute);
	}
	else
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(MenuLevelPath);
		}
	}
}

