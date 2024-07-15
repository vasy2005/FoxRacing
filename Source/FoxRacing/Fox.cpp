// Fill out your copyright notice in the Description page of Project Settings.


#include "Fox.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFox::AFox()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFox::BeginPlay()
{
	Super::BeginPlay();

	/*auto PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		if (Subsystem)
			Subsystem->AddMappingContext(IMC_Dir, 0);
	}*/
}

// Called every frame
void AFox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFox::ChangeDir(const float MovVector)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString(TEXT("LEFT/RIGHT")));
	UE_LOG(LogTemp, Warning, TEXT("LEFT/RIGHT"));

	if (!dirWaiting) return;

	dirSelected = 1;
	if (MovVector < 0) Dir = LEFT;
	else
		Dir = RIGHT;
}

// Called to bind functionality to input
void AFox::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*auto Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input)
	{
		Input->BindAction(IA_Dir, ETriggerEvent::Triggered, this, &AFox::ChangeDir);
	}*/
}

