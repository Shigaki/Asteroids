// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing = OnRep_HealthUpdated, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 Health;

	UPROPERTY(ReplicatedUsing = OnRep_HealthUpdated, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 MaxHealth = 1;

	UPROPERTY(ReplicatedUsing = OnRep_DeadUpdated, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bDead = false ;

public:

	UFUNCTION(BlueprintCallable)
	int32 GetHealth();

	UFUNCTION(BlueprintCallable)
	void SetHealth(int32 InHealth);

	UFUNCTION(BlueprintCallable)
	int32 GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(int32 InHealth);

	UFUNCTION(BlueprintCallable)
	int32 TakeDamage(int32 InDamage);

	UFUNCTION(BlueprintCallable)
	void Die();

	UFUNCTION()
	bool CheckbIsAlive();

	UFUNCTION()
	void OnRep_HealthUpdated();

	UFUNCTION()
	void OnRep_DeadUpdated();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
