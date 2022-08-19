// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(DefaultRoot);

	static ConstructorHelpers::FObjectFinder<USoundBase> SB_ProjectileObj(TEXT("/Game/Core/FX/SFX/SoundCue/SC_GunShot"));
	if (SB_ProjectileObj.Succeeded())
	{
		SB_Projectile = SB_ProjectileObj.Object;
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);

	if (SB_Projectile)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SB_Projectile, GetActorLocation(), 1.f, FMath::RandRange(0.95f, 1.f));
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	Location += GetActorForwardVector() * Speed * DeltaTime;

	SetActorLocation(Location);
}

void AProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AProjectile, Speed);
}

