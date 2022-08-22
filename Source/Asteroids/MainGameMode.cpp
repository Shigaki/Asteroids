// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "AsteroidsPlayerController.h"
#include "ObjectSpawner.h"
#include "Engine/TextRenderActor.h"
#include "Components/TextRenderComponent.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() == ENetMode::NM_ListenServer)
	{
		MaxNumPlayers = 2;
		WaitingPlayersText = GetWorld()->SpawnActor<ATextRenderActor>(ATextRenderActor::StaticClass(), FVector(0.f, 0.f, 100.f), FRotator(90.f, 0.f, -90.f));
		UTextRenderComponent* RenderComponent = WaitingPlayersText->GetTextRender();
		RenderComponent->SetText(FText::FromString(TEXT("Waiting For Players")));
		RenderComponent->SetTextRenderColor(FColor::White);
		RenderComponent->SetWorldSize(72);
		RenderComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
		RenderComponent->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	}
	else if (GetNetMode() == ENetMode::NM_Standalone)
	{
		SetupMatch();
	}
}

void AMainGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllerList.Add(Cast<AAsteroidsPlayerController>(NewPlayer));

	SetMatchState(FName("WaitingToStart"));

	if (NumPlayers == MaxNumPlayers)
	{
		WaitingPlayersText->SetActorHiddenInGame(true);
		SetupMatch();
	}
}

void AMainGameMode::StartMatch()
{
	Super::StartMatch();
}

void AMainGameMode::SetupMatch()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		World->SpawnActor<AObjectSpawner>(AsteroidSpawner, FVector(0.f, 0.f, -1000.f), FRotator::ZeroRotator, SpawnParams);
	}
	StartMatch();
}

void AMainGameMode::EndMatch()
{
	Super::EndMatch();

	for (AAsteroidsPlayerController* PlayerController : PlayerControllerList)
	{
		PlayerController->Client_PopUpEndGameUI();
	}
}

void AMainGameMode::VoteRestartGame(AAsteroidsPlayerController* InPlayer)
{
	if (!InPlayer->bVote)
	{
		InPlayer->bVote = true;
		++NumReadyPlayers;
		if (NumReadyPlayers == NumPlayers)
		{
			RestartGame();
		}
	}
}

void AMainGameMode::EndMatchCheck()
{
	if (NumDeadPlayers == NumPlayers)
	{
		EndMatch();
	}
}

void AMainGameMode::IncrementNumDeadPlayers(bool bIncrement)
{
	bIncrement ? ++NumDeadPlayers : --NumDeadPlayers;
	EndMatchCheck();
}
