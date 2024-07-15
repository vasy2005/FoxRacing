// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceFoxSpline.h"

// Sets default values
ARaceFoxSpline::ARaceFoxSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARaceFoxSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

int32 ARaceFoxSpline::GetSpeed(double WPM)
{
    if (WPM <= 40) return 25;
    if (WPM <= 60) return 30;
    if (WPM <= 80) return 37;
    if (WPM <= 100) return 40;
    return 43;
}

// Called every frame
void ARaceFoxSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

