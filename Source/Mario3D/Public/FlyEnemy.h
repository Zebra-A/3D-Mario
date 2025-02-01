// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "FlyEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MARIO3D_API AFlyEnemy : public AEnemy
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:

	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void Movement() override;
	
private:

	bool IsMoving = true;

private:
	 
	void SetIsMovingTrue();

};
