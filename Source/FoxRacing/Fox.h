// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Fox.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class FOXRACING_API AFox : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFox();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum Directions : bool
	{
		RIGHT = 1,
		LEFT = 0,
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Dir = LEFT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool forward = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool dirSelected = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool dirWaiting = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* IMC_Dir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Dir;

	UFUNCTION(BlueprintCallable)
	void ChangeDir(const float MovVector);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

