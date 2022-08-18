// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AObjectSpawner::AObjectSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	ObjectPooler = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("ObjectPooler"));

	bReplicates = true;
}

// Called when the game starts or when spawned
void AObjectSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ThisClass::Server_Spawn_Implementation, SpawnCooldown, false);
	}
	
}

void AObjectSpawner::Server_Spawn_Implementation()
{
	AAsteroid* PoolableActor = ObjectPooler->GetPooledObject();
	if (PoolableActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Spawn"));
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ThisClass::Server_Spawn_Implementation, SpawnCooldown, false);
		return;
	}
	SpawnLocation = FVector(FMath::RandRange(-1000.f, 1000.f), FMath::RandRange(-700.f, 700.f), 100.f);
	PoolableActor->SetActorLocation(SpawnLocation);
	PoolableActor->SetLifeSpan(LifeSpan);
	PoolableActor->SetActive(true);
	PoolableActor->SetActorRotation(FRotator().ZeroRotator);
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ThisClass::Server_Spawn_Implementation, SpawnCooldown, false);
	UE_LOG(LogTemp, Warning, TEXT("Spawn"));
}

void AObjectSpawner::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AObjectSpawner, SpawnLocation);
}