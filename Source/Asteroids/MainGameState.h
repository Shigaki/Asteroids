// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MainGameState.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE_OneParam(FAddScoreDelegate, int32, InScore);

UCLASS()
class ASTEROIDS_API AMainGameState : public AGameState
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Widget")
	class UScoreWidget* ScoreWidget;

public:

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 Score;

	void UpdateScore(int32 InScore);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
