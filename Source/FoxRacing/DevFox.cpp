// Fill out your copyright notice in the Description page of Project Settings.


#include "DevFox.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADevFox::ADevFox()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADevFox::BeginPlay()
{
	Super::BeginPlay();

	auto MovementComponent = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	MovementComponent->MaxWalkSpeed *= WalkingSpeed;
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
			Subsystem->AddMappingContext(MappingContext, 0);
	}
}

void ADevFox::Move(const FInputActionValue& Value)
{
	auto PC = Cast<APlayerController>(GetController());

	const FVector2D MovVector = Value.Get<FVector2D>();

	const FRotator Rotation = PC->GetControlRotation();
	const FRotator YawRot(0.f, Rotation.Yaw, 0.f);

	const FVector FrwdDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	AddMovementInput(FrwdDir, MovVector.Y);
	const FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDir, MovVector.X);
}

void ADevFox::Rotate(const FInputActionValue& Value)
{
	auto PC = Cast<APlayerController>(GetController());

	const FVector2d RotVector = Value.Get<FVector2D>();

	AddControllerPitchInput(RotVector.Y);
	AddControllerYawInput(RotVector.X);
}

// Called every frame
void ADevFox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADevFox::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input)
	{
		Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ADevFox::Move);
		Input->BindAction(IA_Rotate, ETriggerEvent::Triggered, this, &ADevFox::Rotate);
	}

}

