// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:

	void EndMatchCheck();

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, Category = "AsteroidSpawner")
	TSubclassOf<AActor> AsteroidSpawner;

	int32 MaxNumPlayers = 2;

	TArray<class AAsteroidsPlayerController*> PlayerControllerList;

	int32 NumDeadPlayers = 0;

	int32 NumReadyPlayers = 0;

	class ATextRenderActor* WaitingPlayersText;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void StartMatch() override;

	void SetupMatch();

	virtual void EndMatch() override;

	void VoteRestartGame(AAsteroidsPlayerController* Player);

	void IncrementNumDeadPlayers(bool bIncrement);

};
