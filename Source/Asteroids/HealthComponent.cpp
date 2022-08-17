// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	SetIsReplicated(true);
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(1);
	
}


bool UHealthComponent::CheckbIsAlive()
{
	return !bDead;
}

void UHealthComponent::OnRep_HealthUpdated()
{
	
}

void UHealthComponent::OnRep_DeadUpdated()
{

}

int32 UHealthComponent::GetHealth()
{
	return Health;
}

void UHealthComponent::SetHealth(int32 InHealth)
{
	Health = InHealth;
}

void UHealthComponent::TakeDamage(int32 InDamage)
{
	Health -= InDamage;
	if (Health <= 0)
	{
		Die();
	}
}

void UHealthComponent::Die()
{
	bDead = true;
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHealthComponent, Health);
}