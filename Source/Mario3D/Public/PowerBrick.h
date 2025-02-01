// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerBrick.generated.h"

class UBoxComponent;
class UGeometryCollectionComponent;
class APowerUp;
class AFieldSystemActor;

UCLASS()
class MARIO3D_API APowerBrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerBrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	UPROPERTY(EditAnywhere, Category = "Collision")
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere)
	UGeometryCollectionComponent* BrickGeoCollection;

	UPROPERTY(EditAnywhere, Category = "Power")
	TArray<TSubclassOf<APowerUp>> PowersToSpawn;

	UPROPERTY(EditAnywhere)
	bool IsPowerBrick = false;

	UPROPERTY(EditAnywhere, Category = "ForceField")
	TSubclassOf<AFieldSystemActor> ForceField;

private:

	void SpawnPower();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
