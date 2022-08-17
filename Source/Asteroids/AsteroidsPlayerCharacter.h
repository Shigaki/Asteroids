// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "AsteroidsPlayerCharacter.generated.h"

UCLASS()
class ASTEROIDS_API AAsteroidsPlayerCharacter : public ACharacter
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

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* SpaceshipMeshComponent;


};
