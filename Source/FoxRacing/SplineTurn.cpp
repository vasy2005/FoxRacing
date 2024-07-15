// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineTurn.h"
#include "Math/InterpCurve.h"
#include "Components/SplineComponent.h"


ASplineTurn::ASplineTurn()
{
	PrimaryActorTick.bCanEverTick = true;

}

USplineComponent* ASplineTurn::GetSpl()
{
	return spl;
}

void ASplineTurn::BeginPlay()
{
	Super::BeginPlay();

	turn = 1;
	ABToSpline[a][b] = this;
	ABToSpline[b][a] = this;
}

void ASplineTurn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ASplineTurn* ASplineTurn::GetSpline(int32 Src, int32 Dest)
{
	return ABToSpline[Src][Dest];
}

bool ASplineTurn::GetSplineForwardReverse()
{
	if (reverse)
	{
		if (IDAtDir[a][2] == b || IDAtDir[a][3] == b) return 0;
		else
			return 1;
	}

	if (IDAtDir[b][2] == a || IDAtDir[b][3] == a) return 0;
	else
		return 1;
}

ASplineForward* ASplineTurn::GetSplineForward()
{
	return IDToSpline[(reverse? a : b)];
}
