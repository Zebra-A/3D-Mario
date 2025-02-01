// Fill out your copyright notice in the Description page of Project Settings.


#include "WalkEnemy.h"

#include "FirstPersonCharacter.h"

void AWalkEnemy::BeginPlay()
{
	Super::BeginPlay();

	FirstPointVector = FirstWalkPoint->GetSocketLocation("FirstWalkPoint");
	SecondPointVector = SecondWalkPoint->GetSocketLocation("SecondWalkPoint");
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, SecondPointVector.ToString());


	FirstWalkPoint->DestroyComponent();
	SecondWalkPoint->DestroyComponent();

	FirstPointDir = FirstPointVector - GetActorLocation();
	SecPointDir = SecondPointVector - GetActorLocation();

	FirstRot = GetActorRotation().Yaw;
	SecRot = GetActorRotation().Yaw + 180.f;

}

void AWalkEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AFirstPersonCharacter* Player = Cast<AFirstPersonCharacter>(OtherActor))
	{
		if (SweepResult.Normal.Z == -1.f)
		{
			Destroy();
		}
		else if (!Player->IsInvincible)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Lost");
		}
	}
}

void AWalkEnemy::Movement()
{
	if (IsMovingOnY)
	{
		if (GetActorLocation().Y < FirstPointVector.Y && !IsMovingToSec)
		{
			IsMovingToSec = false;
		}
		else if (GetActorLocation().Y > SecondPointVector.Y)
		{
			IsMovingToSec = true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "unchecked");
			IsMovingToSec = false;
		}

	}
	else
	{
		if (GetActorLocation().X < FirstPointVector.X && !IsMovingToSec)
		{
			IsMovingToSec = false;
		}
		else if (GetActorLocation().X > SecondPointVector.X)
		{
			IsMovingToSec = true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "unchecked");
			IsMovingToSec = false;
		}

	}

	if (!IsMovingToSec)
	{
		SetActorRotation(FRotator(GetActorRotation().Pitch, FirstRot, GetActorRotation().Roll));
		AddMovementInput(FirstPointDir);
	}
	else if (IsMovingToSec)
	{
		SetActorRotation(FRotator(GetActorRotation().Pitch, SecRot, GetActorRotation().Roll));
		AddMovementInput(SecPointDir);
	}

}
