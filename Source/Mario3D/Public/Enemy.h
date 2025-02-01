// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

class USceneComponent;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class MARIO3D_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	USceneComponent* FirstWalkPoint;

	UPROPERTY(EditAnywhere, Category = "AI")
	USceneComponent* SecondWalkPoint;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* EnemyMesh;

	UPROPERTY(EditAnywhere, Category = "Collision")
	UBoxComponent* BodyCollider;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	FVector FirstPointVector{};

	UPROPERTY(VisibleAnywhere, Category = "AI")
	FVector SecondPointVector{};
	
	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool IsMovingToSec = false;

	FVector FirstPointDir{};
	FVector SecPointDir{};

protected:

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Movement();

};
