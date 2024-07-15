// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spline.generated.h"
#define SplineMax 100

class ASplineForward;
class ASplineTurn;

UCLASS()
class FOXRACING_API ASpline : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ASpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	static ASplineForward* IDToSpline[SplineMax];
	static ASplineTurn* ABToSpline[SplineMax][SplineMax];
	static int32 IDAtDir[17][4];
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool turn = 0;

	UFUNCTION(BlueprintCallable)
	int32 GetSpeed(double WPM);

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

//plan
//in BP_SplineForward merge in functie de reverse, dupa gaseste folosind struct id-ul drumului destinatie, dupa care gaseste SplineTurn cu a = ID si b = IDDEST (daca a > b swap si reverse = 1) si apeleaza move pentru acest SplineTurn
//in BP_SplineTurn merge in functie de reverse, dupa gaseste ID-ul drumului destinatie = (reverse? a: b), dupa care gaseste SplineForward cu IDDEST si apeleaza move pt acest SplineForward