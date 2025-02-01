// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"

#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Kismet/KismetMathLibrary.h"

#include "Projectile.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPCamera = CreateDefaultSubobject<UCameraComponent>("FP Camera");
	FPCamera->SetupAttachment(RootComponent);
	FPCamera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
	
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Move);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Look);

		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Jump);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFirstPersonCharacter::StopJumping);

		EnhancedInput->BindAction(FireAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Fire);
	}

}

void AFirstPersonCharacter::Move(const FInputActionValue& InputValue)
{
	const FVector2D InputVector = InputValue.Get<FVector2D>();

	if (Controller)
	{
		const FRotator ControllerRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControllerRotation.Yaw, 0.f);

		const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(FowardDirection, InputVector.X);
		AddMovementInput(RightDirection, InputVector.Y);
	}

}

void AFirstPersonCharacter::Look(const FInputActionValue& InputValue)
{
	const FVector2D InputVector = InputValue.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(InputVector.X * LookSensitivity / 2);
		AddControllerPitchInput(-InputVector.Y * LookSensitivity / 2);
	}

}

void AFirstPersonCharacter::Fire()
{
	if (CanShoot && CurrentBullet > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Magenta, "Shooting");
		FTransform SpawnTransform = UKismetMathLibrary::MakeTransform(FPCamera->GetSocketLocation("FPCamera"), FPCamera->GetSocketRotation("FPCamera"), FVector(1, 1, 1));
		FActorSpawnParameters SpawnPara;
		SpawnPara.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AProjectile>(ProjectileBullet, SpawnTransform, SpawnPara);

		CurrentBullet--;
	}
	else if (CurrentBullet <= 0)
	{
		CanShoot = false;
	}
}

void AFirstPersonCharacter::SetIsInvincibleTrue()
{
	if (IsInvincible)
	{
		GetWorldTimerManager().ClearTimer(SetInvincibleFalseHandle);
	}

	IsInvincible = true;

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Is Invincible");

	GetWorldTimerManager().SetTimer(SetInvincibleFalseHandle, this, &AFirstPersonCharacter::SetIsInvincibleFalse, 5.f);
}

void AFirstPersonCharacter::SetIsInvincibleFalse()
{
	IsInvincible = false;

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Is not Invincible");
}

void AFirstPersonCharacter::SetCanShootTrue()
{
	CurrentBullet = MaxBullet;
	CanShoot = true;
}


