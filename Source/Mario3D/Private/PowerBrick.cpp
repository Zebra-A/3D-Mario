// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerBrick.h"

#include "Components/BoxComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

#include "FirstPersonCharacter.h"
#include "Projectile.h"

#include "PowerUp.h"

#include "Field/FieldSystemActor.h"

// Sets default values
APowerBrick::APowerBrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	RootComponent = BoxCollider;

	BrickGeoCollection = CreateDefaultSubobject<UGeometryCollectionComponent>("GeometryCollection");
	BrickGeoCollection->SetupAttachment(RootComponent);

	PowersToSpawn = {};

}

// Called when the game starts or when spawned
void APowerBrick::BeginPlay()
{
	Super::BeginPlay();

	BoxCollider->OnComponentHit.AddDynamic(this, &APowerBrick::OnHit);
	
}

// Called every frame
void APowerBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerBrick::SpawnPower()
{
	int PowerSelectNum = FMath::RandRange(0, PowersToSpawn.Num() - 1);

	FActorSpawnParameters PowerSpawnParam;
	GetWorld()->SpawnActor<APowerUp>(PowersToSpawn[PowerSelectNum], GetActorLocation(), GetActorRotation(), PowerSpawnParam);
}

void APowerBrick::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, "hit");
	AProjectile* Projectile = Cast<AProjectile>(OtherActor);
	AFirstPersonCharacter* Player = Cast<AFirstPersonCharacter>(OtherActor);
	if ((Player && Hit.Normal.Z == 1.f) || Projectile)
	{
		BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BrickGeoCollection->SetSimulatePhysics(true);
		BrickGeoCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		BrickGeoCollection->OnActorEnableCollisionChanged();

		AFieldSystemActor* FieldSystem;
		if (Player)
		{
			FieldSystem = GetWorld()->SpawnActor<AFieldSystemActor>(ForceField, FTransform(FRotator(0, 0, 0), FVector(Hit.Location.X, Hit.Location.Y, Hit.Location.Z + 80.f), FVector(1, 1, 1)));
		}
		else
		{
			FieldSystem = GetWorld()->SpawnActor<AFieldSystemActor>(ForceField, FTransform(FRotator(0, 0, 0), FVector(Hit.Location.X, Hit.Location.Y, Hit.Location.Z), FVector(1, 1, 1)));

			Projectile->Destroy();
		}

		FieldSystem->SetLifeSpan(2.f);

		if(IsPowerBrick) SpawnPower();

		SetLifeSpan(4.f);
	}
}

