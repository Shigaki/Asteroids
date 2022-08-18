// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaBounds.h"
#include "Components/BoxComponent.h"
#include "TeleportInterface.h"

// Sets default values
AArenaBounds::AArenaBounds()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LeftBound = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftBound"));
	LeftBound->SetupAttachment(RootComponent);
	RightBound = CreateDefaultSubobject<UBoxComponent>(TEXT("RightBound"));
	RightBound->SetupAttachment(RootComponent);
	UpperBound = CreateDefaultSubobject<UBoxComponent>(TEXT("UpperBound"));
	UpperBound->SetupAttachment(RootComponent);
	BottomBound = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomBound"));
	BottomBound->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AArenaBounds::BeginPlay()
{
	Super::BeginPlay();

	LeftBound->SetWorldScale3D(FVector(0.1f, 6.f, 1.f));
	LeftBound->SetWorldLocation(FVector(-1010.f, 0.f, 100.f));
	RightBound->SetWorldScale3D(FVector(0.1f, 6.f, 1.f));
	RightBound->SetWorldLocation(FVector(1010.f, 0.f, 100.f));

	UpperBound->SetWorldScale3D(FVector(10.f, 0.1f, 1.f));
	UpperBound->SetWorldLocation(FVector(0.f, -610.f, 100.f));
	BottomBound->SetWorldScale3D(FVector(0.1f, 6.f, 1.f));
	BottomBound->SetWorldLocation(FVector(10.f, 0.1f, 100.f));

	LeftBound->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd_Horizontal);
	RightBound->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd_Horizontal);

	UpperBound->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd_Vertical);
	BottomBound->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd_Vertical);

}

void AArenaBounds::OnOverlapEnd_Horizontal(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ITeleportInterface::Execute_Teleport(OtherActor);
}

void AArenaBounds::OnOverlapEnd_Vertical(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ITeleportInterface::Execute_Teleport(OtherActor);
}
