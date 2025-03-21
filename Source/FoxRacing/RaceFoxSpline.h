// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RaceFoxSpline.generated.h"

UCLASS()
class FOXRACING_API ARaceFoxSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARaceFoxSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	int32 GetSpeed(double WPM);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
