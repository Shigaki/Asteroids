// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"

AAsteroid::AAsteroid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(DefaultRoot);

	SetActorEnableCollision(false);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	SetReplicates(true);
	SetReplicateMovement(true);
}

void AAsteroid::SetLifeSpan(float InLifeSpan)
{
	LifeSpan = InLifeSpan;
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &ThisClass::Deactivate, LifeSpan, false);
}

void AAsteroid::SetActive(bool InActive)
{
	if (InActive)
	{
		HealthComponent->SetHealth(HealthComponent->GetMaxHealth());
	}
	bActive = InActive;
	SetActorHiddenInGame(!InActive);
}

bool AAsteroid::IsActive()
{
	return bActive;
}

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	Size = static_cast<ESize>(FMath::RandRange(0, 2));

	switch(Size)
	{
		case ESize::Small:
			Mesh->SetWorldScale3D(FVector(3.f, 3.f, 3.f));
			Speed = FMath::RandRange(100.f, 200.f);
			HealthComponent->SetMaxHealth(1);
			break;
		case ESize::Medium:
			Mesh->SetWorldScale3D(FVector(8.f, 8.f, 8.f));
			Speed = FMath::RandRange(40.f, 80.f);
			HealthComponent->SetMaxHealth(2);
			break;
		case ESize::Large:
			Mesh->SetWorldScale3D(FVector(13.f, 13.f, 13.f));
			Speed = FMath::RandRange(20.f, 60.f);
			HealthComponent->SetMaxHealth(3);
			break;
	}

	RollValue  = FMath::RandRange(-Speed, Speed);
	PitchValue = FMath::RandRange(-Speed, Speed);
	YawValue   = FMath::RandRange(-Speed, Speed);
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rotation;
	Rotation.Roll	= RollValue * DeltaTime;
	Rotation.Pitch	= PitchValue * DeltaTime;
	Rotation.Yaw	= YawValue * DeltaTime;

	Mesh->AddLocalRotation(Rotation);

	FVector Location = GetActorLocation();
	Location += GetActorForwardVector() * Speed * DeltaTime;

	SetActorLocation(Location);
}

void AAsteroid::Deactivate()
{
	SetActive(false);
}

float AAsteroid::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString(TEXT("Hit"))
		);
	}
	if (HealthComponent->TakeDamage(FMath::RoundToInt32(DamageAmount) <= 0))
	{
		Deactivate();
	}
	return DamageAmount;
}

void AAsteroid::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAsteroid, bActive);
	DOREPLIFETIME(AAsteroid, Size);
	DOREPLIFETIME(AAsteroid, Speed);
}