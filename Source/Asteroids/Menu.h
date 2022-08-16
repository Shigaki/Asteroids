// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void MenuSetup();

protected:

	virtual bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UButton* Menu_PlayButton;
	UPROPERTY(meta = (BindWidget))
	UButton* Menu_SettingsButton;
	UPROPERTY(meta = (BindWidget))
	UButton* Menu_ExitButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Play_SinglePlayerButton;
	UPROPERTY(meta = (BindWidget))
	UButton* Play_MultiPlayerButton;
	UPROPERTY(meta = (BindWidget))
	UButton* Play_BackButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MP_HostButton;
	UPROPERTY(meta = (BindWidget))
	UButton* MP_JoinButton;
	UPROPERTY(meta = (BindWidget))
	UButton* MP_BackButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UButton* Lobby_RefreshButton;
	UPROPERTY(meta = (BindWidget))
	UButton* Lobby_BackButton;

	UPROPERTY(meta = (BindWidget))
	UButton* Settings_BackButton;

	UFUNCTION()
	void Menu_PlayButtonClicked();
	UFUNCTION()
	void Menu_SettingsButtonClicked();
	UFUNCTION()
	void Menu_ExitButtonClicked();

	UFUNCTION()
	void Play_SinglePlayerButtonClicked();
	UFUNCTION()
	void Play_MultiPlayerButtonClicked();
	UFUNCTION()
	void Play_BackButtonClicked();

	UFUNCTION()
	void MP_HostButtonClicked();
	UFUNCTION()
	void MP_JoinButtonClicked();
	UFUNCTION()
	void MP_BackButtonClicked();

	UFUNCTION()
	void Lobby_RefreshButtonClicked();
	UFUNCTION()
	void Lobby_BackButtonClicked();

	UFUNCTION()
	void Settings_BackButtonClicked();

	void MenuTearDown();

	FString MainLevelPath{ TEXT("/Game/Core/Maps/MainLevel") };

};
