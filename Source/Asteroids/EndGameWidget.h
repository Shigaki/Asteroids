// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDS_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual bool Initialize() override;
	
public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FinalScoreText;
	UPROPERTY(meta = (BindWidget))
	class UButton* RetryButton;
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	
	UFUNCTION(BlueprintCallable)
	void UpdateFinalScoreText(int32 InScore);

	UFUNCTION()
	void RetryButtonClicked();
	UFUNCTION()
	void QuitButtonClicked();

	FString MenuLevelPath{ TEXT("/Game/Core/Maps/MenuLevel") };
};
