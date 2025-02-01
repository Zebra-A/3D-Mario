// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(FName("SphereCollider"));
	RootComponent = SphereCollider;

	PowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PowerMesh"));
	PowerMesh->SetupAttachment(SphereCollider);

}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

