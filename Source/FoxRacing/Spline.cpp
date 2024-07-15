// Fill out your copyright notice in the Description page of Project Settings.

#include "Spline.h"

ASplineForward* ASpline::IDToSpline[SplineMax];
ASplineTurn* ASpline::ABToSpline[SplineMax][SplineMax];
int32 ASpline::IDAtDir[17][4] = { 0, 0, 0, 0,
								 2, 3, 0, 0,
								 4, 5, 3, 1,
								 7, 8, 1, 2,
                                 11, 10, 5, 2,
                                 6, 7, 2, 4,
                                 10, 9, 7, 5,
                                 8, 3, 5, 6, 
                                 9, 12, 3, 7,
                                 12, 8, 6, 10,
                                 4, 11, 9, 6,
                                 14, 13, 10, 4,
                                 0, 0, 8, 9,
                                 0, 0, 11, 14,
                                 16, 15, 13, 11,
                                 0, 0, 14, 16,
                                 0, 0, 15, 14};

// Sets default values
ASpline::ASpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpline::BeginPlay()
{
	Super::BeginPlay();
	
}

int32 ASpline::GetSpeed(double WPM)
{
    if (WPM <= 40) return 25;
    if (WPM <= 60) return 30;
    if (WPM <= 80) return 37;
    if (WPM <= 100) return 40;
    return 43;
}

// Called every frame
void ASpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}