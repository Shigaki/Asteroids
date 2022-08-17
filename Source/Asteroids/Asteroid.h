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
	
protected:
	virtual void BeginPlay() override;

	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	TEnumAsByte<ESize> Size;
	
};
