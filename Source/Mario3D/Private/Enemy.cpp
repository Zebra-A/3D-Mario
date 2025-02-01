// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyCollider = CreateDefaultSubobject<UBoxComponent>("BodyCollider");
	RootComponent = BodyCollider;

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>("EnemyMesh");
	EnemyMesh->SetupAttachment(RootComponent);

	FirstWalkPoint = CreateDefaultSubobject<USceneComponent>("FirstWalkPoint");
	FirstWalkPoint->SetupAttachment(RootComponent);

	SecondWalkPoint = CreateDefaultSubobject<USceneComponent>("SecondWalkPoint");
	SecondWalkPoint->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	BodyCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Movement();

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AEnemy::Movement()
{

}

