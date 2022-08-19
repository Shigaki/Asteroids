// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UENUM()
enum ESize
{
	Small		UMETA(DisplayName = "Small"),
	Medium      UMETA(DisplayName = "Medium"),
	Large		UMETA(DisplayName = "Large"),
};

UCLASS()
class ASTEROIDS_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:

	AAsteroid();

	virtual void SetLifeSpan(float InLifeSpan) override;

	void SetActive(bool InActive);

	bool IsActive();

	void Deactivate();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* DefaultRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Audio")
	class USoundBase* SB_Explosion;
	
	float LifeSpan = 20.f;
	FTimerHandle LifeSpanTimer;
	
	UPROPERTY(VisibleAnywhere)
	float RotateSpeed;
	UPROPERTY(VisibleAnywhere)
	float RollValue;
	UPROPERTY(VisibleAnywhere)
	float PitchValue;
	UPROPERTY(VisibleAnywhere)
	float YawValue;

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_PlayExplosionSound();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	class UHealthComponent* HealthComponent;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Replicated, EditAnywhere, Category = "Properties")
	TEnumAsByte<ESize> Size;

	UPROPERTY(Replicated)
	bool bActive;

	UPROPERTY(Replicated, EditAnywhere)
	float Speed;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
