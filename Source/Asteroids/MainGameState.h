// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MainGameState.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API AMainGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	int32 Score;

	void AddScore(int32 InScore);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
