// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolComponent.h"

// Sets default values for this component's properties
UObjectPoolComponent::UObjectPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


AAsteroid* UObjectPoolComponent::GetPooledObject()
{
	for (AAsteroid* PoolableActor : Pool)
	{
		if (!PoolableActor->IsActive())
		{
			return PoolableActor;
		}
	}
	return nullptr;
}

// Called when the game starts
void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (PooledObjectSubclass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				AAsteroid* PoolableActor = GetWorld()->SpawnActor<AAsteroid>(PooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
				PoolableActor->SetActive(false);
				Pool.Add(PoolableActor);
				UE_LOG(LogTemp, Warning, TEXT("Added Object to Pool"));
			}
		}
	}
	
}
