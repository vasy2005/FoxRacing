// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceEnemySpline.h"

// Sets default values
ARaceEnemySpline::ARaceEnemySpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARaceEnemySpline::BeginPlay()
{
	Super::BeginPlay();
	
}

int32 ARaceEnemySpline::GetSpeed(double WPM)
{
    if (WPM <= 40) return 25;
    if (WPM <= 60) return 30;
    if (WPM <= 80) return 37;
    if (WPM <= 100) return 40;
    return 43;
}

// Called every frame
void ARaceEnemySpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

