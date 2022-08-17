// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	switch(Size)
	{
		case ESize::Small:
			Mesh->SetWorldScale3D(FVector(3.f, 3.f, 3.f));
			RotateSpeed = 120.f;
			break;
		case ESize::Medium:
			Mesh->SetWorldScale3D(FVector(8.f, 8.f, 8.f));
			RotateSpeed = 40.f;
			break;
		case ESize::Large:
			Mesh->SetWorldScale3D(FVector(13.f, 13.f, 13.f));
			RotateSpeed = 20.f;
			break;
	}

	RollValue  = FMath::RandRange(-RotateSpeed, RotateSpeed);
	PitchValue = FMath::RandRange(-RotateSpeed, RotateSpeed);
	YawValue   = FMath::RandRange(-RotateSpeed, RotateSpeed);
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rotation;
	Rotation.Roll	= RollValue * DeltaTime;
	Rotation.Pitch	= PitchValue * DeltaTime;
	Rotation.Yaw	= YawValue * DeltaTime;

	Mesh->AddLocalRotation(Rotation);
}