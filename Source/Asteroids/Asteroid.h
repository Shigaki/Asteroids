// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Asteroid.generated.h"

UENUM()
enum ESize
{
	Small		UMETA(DisplayName = "Small"),
	Medium      UMETA(DisplayName = "Medium"),
	Large		UMETA(DisplayName = "Large"),
};

/**
 * 
 */
UCLASS()
class ASTEROIDS_API AAsteroid : public AProjectile
{
	GENERATED_BODY()
	
public:

	AAsteroid();

	virtual void SetLifeSpan(float InLifeSpan) override;
	void SetActive(bool InActive);
	bool IsActive();

protected:
	virtual void BeginPlay() override;
	
	float LifeSpan = 20.f;
	FTimerHandle LifeSpanTimer;
	bool bActive;
	void Deactivate();

	UPROPERTY(VisibleAnywhere)
	float RotateSpeed;
	UPROPERTY(VisibleAnywhere)
	float RollValue;
	UPROPERTY(VisibleAnywhere)
	float PitchValue;
	UPROPERTY(VisibleAnywhere)
	float YawValue;

private:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	class UHealthComponent* HealthComponent;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	TEnumAsByte<ESize> Size;

	UPROPERTY(EditAnywhere, Category = "Properties")
	int32 PoolValue = 1;
	
};
