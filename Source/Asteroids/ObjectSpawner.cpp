// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

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
	
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ThisClass::Spawn, SpawnCooldown, false);
}

float AObjectSpawner::GetLifeSpan()
{
	return LifeSpan;
}

void AObjectSpawner::Spawn()
{
	ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AAsteroid* PoolableActor = ObjectPooler->GetPooledObject();
	if (PoolableActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Spawn"));
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ThisClass::Spawn, SpawnCooldown, false);
		return;
	}
	FVector SpawnLocation = MyCharacter->GetNavAgentLocation();
	SpawnLocation.Z = 100.f;
	PoolableActor->SetActorLocation(SpawnLocation);
	PoolableActor->SetLifeSpan(LifeSpan);
	PoolableActor->SetActive(true);
	PoolableActor->SetActorRotation(MyCharacter->GetActorRotation());
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &ThisClass::Spawn, SpawnCooldown, false);
	UE_LOG(LogTemp, Warning, TEXT("Spawn"));
}

