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
	
public:

	int32 MaxNumPlayers;
	TArray<class APlayerController*> PlayerControllerList;


	virtual bool ReadyToStartMatch_Implementation() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;


};
