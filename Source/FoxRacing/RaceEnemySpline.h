// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RaceEnemySpline.generated.h"

UCLASS()
class FOXRACING_API ARaceEnemySpline : public AActor
{
	GENERATED_BODY()

	int timer = 0;
	int sec = 0;

public:	
	// Sets default values for this actor's properties
	ARaceEnemySpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	int32 GetSpeed(double WPM);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float wpm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float minwpm;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
