// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AsteroidsPlayerCharacter.generated.h"

UCLASS()
class ASTEROIDS_API AAsteroidsPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAsteroidsPlayerCharacter();

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> ProjectileActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void FireProjectile();
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_FireProjectile();
	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_FireProjectile();

	void MoveForward(float Value);
	void TurnRight(float Value);

	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* Muzzle;

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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
