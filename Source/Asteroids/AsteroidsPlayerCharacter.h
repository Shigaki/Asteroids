// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TeleportInterface.h"
#include "AsteroidsPlayerCharacter.generated.h"

UCLASS()
class ASTEROIDS_API AAsteroidsPlayerCharacter : public ACharacter, public ITeleportInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAsteroidsPlayerCharacter();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void FireProjectile();

	void MoveForward(float Value);
	void TurnRight(float Value);

	class UHealthComponent* HealthComponent;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(Replicated)
	bool bDead = false;

	UFUNCTION(BlueprintCallable)
	bool IsDead();

	UFUNCTION(BlueprintCallable)
	void Ressurect();

	void EnterGhostMode();

	// Teleport Interface
	/*
	bool bCanTeleport = true;
	float TeleportCooldown = 1.f;
	FTimerHandle TeleportCooldownTimer;

	virtual void Teleport_Implementation() override;
	void SetTeleportOnCooldown();
	*/

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
