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

	int32 MaxNumPlayers = 2;
	TArray<class APlayerController*> PlayerControllerList;

	int32 NumDeadPlayers = 0;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void EndMatch() override;

	void IncrementNumDeadPlayers(bool bIncrement);

};
