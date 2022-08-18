// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidsPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "HealthComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AAsteroidsPlayerCharacter::AAsteroidsPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AAsteroidsPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AAsteroidsPlayerCharacter::FireProjectile()
{
}

void AAsteroidsPlayerCharacter::MoveForward(float Value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	FVector Direction = UKismetMathLibrary::GetForwardVector(YawRotation);
	AddMovementInput(Direction, Value);
}

void AAsteroidsPlayerCharacter::TurnRight(float Value)
{
	AddControllerYawInput(Value);
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
	if (HealthComponent->TakeDamage(FMath::RoundToInt32(DamageAmount) <= 0))
	{
		GhostMode(true);
	}
	return DamageAmount;
}

bool AAsteroidsPlayerCharacter::GhostMode(bool)
{
	// TODO - revive mechanic
	return false;
}

/*
void AAsteroidsPlayerCharacter::Teleport_Implementation()
{
	if (bCanTeleport)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TELEPORTING"));
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 100.f), false, nullptr, ETeleportType::TeleportPhysics);
	}
	bCanTeleport = false;
	GetWorldTimerManager().SetTimer(TeleportCooldownTimer, this, &ThisClass::SetTeleportOnCooldown, TeleportCooldown, false);
}

void AAsteroidsPlayerCharacter::SetTeleportOnCooldown()
{
	bCanTeleport = true;
}
*/
