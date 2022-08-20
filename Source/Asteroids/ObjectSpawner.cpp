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
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ThisClass::Spawn, SpawnCooldown, false, 3.f);
	}
}

void AObjectSpawner::Spawn()
{
	AAsteroid* PoolableActor = ObjectPooler->GetPooledObject();
	if (PoolableActor == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Cannot Spawn"));
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ThisClass::Spawn, SpawnCooldown, false);
		return;
	}
	SpawnLocation.X = FMath::RandRange(800.f, 1000.f) * (FMath::RandBool() ? 1 : -1);
	SpawnLocation.Y	= FMath::RandRange(600.f, 700.f)  * (FMath::RandBool() ? 1 : -1);
	SpawnLocation.Z = 100.f;
	PoolableActor->SetActorLocation(SpawnLocation);
	PoolableActor->SetActorRotation(FRotator(0.f, FMath::RandRange(0.f, 360.f), 0.f));
	PoolableActor->SetLifeSpan(LifeSpan);
	PoolableActor->SetActive(true);
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ThisClass::Spawn, SpawnCooldown, false);
	//UE_LOG(LogTemp, Warning, TEXT("Spawn"));
}
