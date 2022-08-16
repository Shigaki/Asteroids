// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenu::MenuSetup()
{
	
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (Menu_PlayButton)
	{
		Menu_PlayButton->OnClicked.AddDynamic(this, &ThisClass::Menu_PlayButtonClicked);
	}
	if (Menu_SettingsButton)
	{
		Menu_SettingsButton->OnClicked.AddDynamic(this, &ThisClass::Menu_SettingsButtonClicked);
	}
	if (Menu_ExitButton)
	{
		Menu_ExitButton->OnClicked.AddDynamic(this, &ThisClass::Menu_ExitButtonClicked);
	}

	
	if (Play_SinglePlayerButton)
	{
		Play_SinglePlayerButton->OnClicked.AddDynamic(this, &ThisClass::Play_SinglePlayerButtonClicked);
	}
	if (Play_MultiPlayerButton)
	{
		Play_MultiPlayerButton->OnClicked.AddDynamic(this, &ThisClass::Play_MultiPlayerButtonClicked);
	}
	if (Play_BackButton)
	{
		Play_BackButton->OnClicked.AddDynamic(this, &ThisClass::Play_BackButtonClicked);
	}

	if (MP_HostButton)
	{
		MP_HostButton->OnClicked.AddDynamic(this, &ThisClass::MP_HostButtonClicked);
	}
	if (MP_JoinButton)
	{
		MP_JoinButton->OnClicked.AddDynamic(this, &ThisClass::MP_JoinButtonClicked);
	}
	if (MP_BackButton)
	{
		MP_BackButton->OnClicked.AddDynamic(this, &ThisClass::MP_BackButtonClicked);
	}

	if (Lobby_RefreshButton)
	{
		Lobby_RefreshButton->OnClicked.AddDynamic(this, &ThisClass::Lobby_RefreshButtonClicked);
	}
	if (Lobby_BackButton)
	{
		Lobby_BackButton->OnClicked.AddDynamic(this, &ThisClass::Lobby_BackButtonClicked);
	}

	if (Settings_BackButton)
	{
		Settings_BackButton->OnClicked.AddDynamic(this, &ThisClass::Settings_BackButtonClicked);
	}

	return true;
}

void UMenu::Lobby_RefreshButtonClicked()
{
	// find online sessions
}

void UMenu::Lobby_BackButtonClicked()
{
	WidgetSwitcher->SetActiveWidgetIndex(2);
}

void UMenu::Settings_BackButtonClicked()
{
	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void UMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}

void UMenu::Menu_PlayButtonClicked()
{
	WidgetSwitcher->SetActiveWidgetIndex(1);
}

void UMenu::Menu_SettingsButtonClicked()
{
	WidgetSwitcher->SetActiveWidgetIndex(4);
}

void UMenu::Menu_ExitButtonClicked()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, false);
	}
}

void UMenu::Play_SinglePlayerButtonClicked()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel(MainLevelPath);
	}
}

void UMenu::Play_MultiPlayerButtonClicked()
{
	WidgetSwitcher->SetActiveWidgetIndex(2);
}

void UMenu::Play_BackButtonClicked()
{
	WidgetSwitcher->SetActiveWidgetIndex(0);
}

void UMenu::MP_HostButtonClicked()
{
	// create online match
}

void UMenu::MP_JoinButtonClicked()
{
	WidgetSwitcher->SetActiveWidgetIndex(3);
}

void UMenu::MP_BackButtonClicked()
{
	WidgetSwitcher->SetActiveWidgetIndex(1);
}
