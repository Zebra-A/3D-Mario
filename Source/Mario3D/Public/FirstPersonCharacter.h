// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FirstPersonCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class AProjectile;

UCLASS()
class MARIO3D_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Input
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;


	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Sensitivity")
	float LookSensitivity = 5.f;

	// Shoot
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot Power", meta = (AllowPrivateAccess = "true"))
	int MaxBullet = 3;

	UPROPERTY(BlueprintReadOnly, Category = "Shoot Power", meta = (AllowPrivateAccess = "true"))
	int CurrentBullet{};

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileBullet;

	// Camera
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* FPCamera;

	// Powers
	FTimerHandle SetInvincibleFalseHandle;

public:
	// Power State
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Powers")
	bool IsInvincible = false;

	UPROPERTY(EditAnywhere, Category = "Powers")
	bool CanShoot = false;


private:

	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);

	void Fire();
	
	UFUNCTION(BlueprintCallable)
	void SetIsInvincibleTrue();
	void SetIsInvincibleFalse();

	UFUNCTION(BlueprintCallable)
	void SetCanShootTrue();

};
