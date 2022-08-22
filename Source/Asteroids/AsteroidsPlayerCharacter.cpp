// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidsPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MainGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Projectile.h"

// Sets default values
AAsteroidsPlayerCharacter::AAsteroidsPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(RootComponent);
	Muzzle->SetRelativeLocation(FVector(40.f, 0.f, 0.f));

	SpaceshipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceshipMesh"));
	SpaceshipMesh->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	bGenerateOverlapEventsDuringLevelStreaming = false;
	SpaceshipMesh->SetGenerateOverlapEvents(false);

	static ConstructorHelpers::FObjectFinder<USoundBase> SB_ShutdownObj(TEXT("/Game/Core/FX/SFX/SoundCue/SC_ShipDestroyed"));
	if (SB_ShutdownObj.Succeeded())
	{
		SB_Shutdown = SB_ShutdownObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB_RessurectObj(TEXT("/Game/Core/FX/SFX/SoundCue/SC_RessurectEnd"));
	if (SB_RessurectObj.Succeeded())
	{
		SB_Ressurect = SB_RessurectObj.Object;
	}

	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AAsteroidsPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	bGenerateOverlapEventsDuringLevelStreaming = true;
	SpaceshipMesh->SetGenerateOverlapEvents(true);
}

void AAsteroidsPlayerCharacter::FireProjectile()
{
	if (!bDead)
	{
		if (HasAuthority())
		{
			Multicast_FireProjectile();
		}
		else
		{
			Server_FireProjectile();
		}
	}
}

void AAsteroidsPlayerCharacter::Server_FireProjectile_Implementation()
{
	Multicast_FireProjectile();
}

bool AAsteroidsPlayerCharacter::Server_FireProjectile_Validate()
{
	return true;
}

void AAsteroidsPlayerCharacter::Multicast_FireProjectile_Implementation()
{
	if (!bDead)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			
			World->SpawnActor<AProjectile>(ProjectileActor, Muzzle->GetComponentLocation(), GetActorRotation(), SpawnParams);
		}
	}
}

void AAsteroidsPlayerCharacter::MoveForward(float Value)
{
	if (!bDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		FVector Direction = UKismetMathLibrary::GetForwardVector(YawRotation);
		AddMovementInput(Direction, Value);
	}
}

void AAsteroidsPlayerCharacter::TurnRight(float Value)
{
	if (!bDead)
	{
		AddControllerYawInput(Value);
	}
}

void AAsteroidsPlayerCharacter::Multicast_PlayShutdownSound_Implementation()
{
	if (SB_Shutdown)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SB_Shutdown, GetActorLocation());
	}
}

void AAsteroidsPlayerCharacter::Multicast_PlayRessurectSound_Implementation()
{
	if (SB_Ressurect)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SB_Ressurect, GetActorLocation());
	}
}

// Called to bind functionality to input
void AAsteroidsPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("FireProjectile", EInputEvent::IE_Pressed, this, &ThisClass::FireProjectile);

	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("TurnRight", this, &ThisClass::TurnRight);

}

float AAsteroidsPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (HealthComponent->TakeDamage(FMath::RoundToInt32(DamageAmount)) <= 0)
	{
		//Multicast_PlayShutdownSound();
		bDead = true;
		EnterGhostMode();
		UWorld* World = GetWorld();
		if (World)
		{
			AMainGameMode* MainGameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(World));
			MainGameMode->IncrementNumDeadPlayers(bDead);
		}
	}
	return DamageAmount;
}

bool AAsteroidsPlayerCharacter::IsDead()
{
	return bDead;
}

void AAsteroidsPlayerCharacter::Ressurect()
{
	Multicast_PlayRessurectSound();
	HealthComponent->SetHealth(HealthComponent->GetMaxHealth());
	//remove mesh transparency
	bDead = false;
	UWorld* World = GetWorld();
	if (World)
	{
		AMainGameMode* MainGameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(World));
		MainGameMode->IncrementNumDeadPlayers(bDead);
	}
}

void AAsteroidsPlayerCharacter::EnterGhostMode()
{
	//apply mesh transparency
}

void AAsteroidsPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAsteroidsPlayerCharacter, bDead);
}