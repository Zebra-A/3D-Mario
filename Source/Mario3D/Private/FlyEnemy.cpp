// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyEnemy.h"

#include "FirstPersonCharacter.h"

void AFlyEnemy::BeginPlay()
{
	Super::BeginPlay();

	FirstPointVector = FirstWalkPoint->GetSocketLocation("FirstWalkPoint");
	SecondPointVector = SecondWalkPoint->GetSocketLocation("SecondWalkPoint");

	FirstWalkPoint->DestroyComponent();
	SecondWalkPoint->DestroyComponent();

	FirstPointDir = FirstPointVector - GetActorLocation();
	SecPointDir = SecondPointVector - GetActorLocation();

}

void AFlyEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AFirstPersonCharacter* Player = Cast<AFirstPersonCharacter>(OtherActor))
	{
		if (!Player->IsInvincible)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Lost");
		}
	}
}

void AFlyEnemy::Movement()
{
	if (IsMoving)
	{
		if (GetActorLocation().Z < FirstPointVector.Z && !IsMovingToSec)
		{
			AddMovementInput(FirstPointDir);
		}
		else if (GetActorLocation().Z >= FirstPointVector.Z && !IsMovingToSec)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "First");
			IsMovingToSec = true;
			IsMoving = false;

			FTimerHandle SetMovingHandle;
			GetWorldTimerManager().SetTimer(SetMovingHandle, this, &AFlyEnemy::SetIsMovingTrue, 2.f);
		}

		if (GetActorLocation().Z > SecondPointVector.Z && IsMovingToSec)
		{
			AddMovementInput(SecPointDir);
		}
		else if (GetActorLocation().Z <= SecondPointVector.Z && IsMovingToSec)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Sec");
			IsMovingToSec = false;
			IsMoving = false;

			FTimerHandle SetMovingHandle;
			GetWorldTimerManager().SetTimer(SetMovingHandle, this, &AFlyEnemy::SetIsMovingTrue, 3.f);
		}
	}
}

void AFlyEnemy::SetIsMovingTrue()
{
	IsMoving = true;
}
