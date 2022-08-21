// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AsteroidsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API AAsteroidsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
	
public:

	bool bVote = false;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> EndGameWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Widget")
	class UEndGameWidget* EndGameWidget;

	UFUNCTION(Client, Reliable)
	void Client_PopUpEndGameUI();

	UFUNCTION()
	bool VoteRestart();

	UFUNCTION(Server, Reliable)
	void Server_VoteRestart();
};
