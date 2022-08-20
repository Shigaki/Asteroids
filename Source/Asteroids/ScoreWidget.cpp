// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "Components/TextBlock.h"

void UScoreWidget::UpdateScoreText(int32 InScore)
{
	ScoreText->SetText(FText::FromString(FString::FromInt(InScore)));
}
