// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	switch(Size)
	{
		case ESize::Small:
			Mesh->SetWorldScale3D(FVector(3.f, 3.f, 3.f));
			break;
		case ESize::Medium:
			Mesh->SetWorldScale3D(FVector(8.f, 8.f, 8.f));
			break;
		case ESize::Large:
			Mesh->SetWorldScale3D(FVector(13.f, 13.f, 13.f));
			break;
	}

}