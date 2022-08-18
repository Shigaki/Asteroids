// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Asteroid.h"
#include "ObjectPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPoolComponent();
	AAsteroid* GetPooledObject();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
	TSubclassOf<AAsteroid> PooledObjectSubclass;
	
	UPROPERTY(Replicated, EditAnywhere, Category = "ObjectPooler")
	int32 PoolSize = 10;

	UPROPERTY(Replicated)
	TArray<AAsteroid*> Pool;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
