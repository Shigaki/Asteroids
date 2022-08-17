// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.h"
#include "ObjectPoolComponent.h"
#include "ObjectSpawner.generated.h"

UCLASS()
class ASTEROIDS_API AObjectSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float GetLifeSpan();
	class UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	UObjectPoolComponent* ObjectPooler;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	bool bTrigger;
	
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float LifeSpan = 0.f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnCooldown = 1.2f;

	FTimerHandle SpawnCooldownTimer;

	void Spawn();
};
