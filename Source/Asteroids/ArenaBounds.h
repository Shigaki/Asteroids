// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArenaBounds.generated.h"

UCLASS()
class ASTEROIDS_API AArenaBounds : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArenaBounds();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	class UBoxComponent* LeftBound;
	UBoxComponent* RightBound;
	UBoxComponent* UpperBound;
	UBoxComponent* BottomBound;

	UFUNCTION()
	void OnOverlapEnd_Horizontal(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnOverlapEnd_Vertical(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
