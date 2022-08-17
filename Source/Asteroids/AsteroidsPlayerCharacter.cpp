// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidsPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AAsteroidsPlayerCharacter::AAsteroidsPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpaceshipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceshipMesh"));
	SpaceshipMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AAsteroidsPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpaceshipMeshComponent->BodyInstance.bLockXRotation = true;
	SpaceshipMeshComponent->BodyInstance.bLockYRotation = true;
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

