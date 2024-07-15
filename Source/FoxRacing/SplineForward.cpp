// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineForward.h"
#include "SplineTurn.h"
#include "Components/SplineComponent.h"
#include "UObject/UObjectGlobals.h"
#include "Math/InterpCurve.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Engine/World.h"

ASplineForward::ASplineForward()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASplineForward::BeginPlay()
{
	Super::BeginPlay();

	turn = 0;
	IDToSpline[ID] = this;
}

void ASplineForward::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ASplineForward* ASplineForward::GetSpline(int32 SplineID)
{
	return IDToSpline[SplineID];
}

int32 ASplineForward::GetIDAtDir(bool Dir)
{
	return IDAtDir[ID][(reverse ? (Dir ? 3 : 2) : (Dir ? 1 : 0))];
}

ASplineTurn* ASplineForward::GetSplineTurn(int32 a, int32 b)
{
	return ABToSpline[a][b];
}

ASplineTurn* ASplineForward::CreateSplineTurn(int32 a, int32 b)
{
	ASplineForward* Spline1 = GetSpline(a);
	ASplineForward* Spline2 = GetSpline(b);
	ASplineTurn* SplineTurn = ABToSpline[a][b];
	/*if (SplineTurn == nullptr) FGenericPlatformMisc::RequestExit(false);
	if (SplineTurn->isReady) return SplineTurn;*/

	SplineTurn->reverse = (a > b);

	double Spline1Len = Spline1->spl->GetSplineLength();
	double x, y;
	if (!Spline1->reverse) x = 0.9999, y = 1.000;
	else x = 0.00001, y = 0.000;
	FVector A1 = Spline1->spl->GetLocationAtDistanceAlongSpline(FMath::Lerp(0, Spline1Len, x), ESplineCoordinateSpace::World);
	FVector B1 = Spline1->spl->GetLocationAtDistanceAlongSpline(FMath::Lerp(0, Spline1Len, y), ESplineCoordinateSpace::World);

	if (IDAtDir[b][2] == a || IDAtDir[b][3] == a) x = 0.00001, y = 0.000;
	else x = 0.9999, y = 1.000;

	float Spline2Len = Spline2->spl->GetSplineLength();
	FVector A2 = Spline2->spl->GetLocationAtDistanceAlongSpline(FMath::Lerp(0, Spline2Len, x), ESplineCoordinateSpace::World);
	FVector B2 = Spline2->spl->GetLocationAtDistanceAlongSpline(FMath::Lerp(0, Spline2Len, y), ESplineCoordinateSpace::World);

	if (a > b)
	{
		FVector aux;
		aux = A1;
		A1 = A2;
		A2 = aux;

		aux = B1;
		B1 = B2;
		B2 = aux;
	}

	float m1 = (B1.Y - A1.Y) / (B1.X - A1.X);
	float m2 = (B2.Y - A2.Y) / (B2.X - A2.X);

	float b1 = A1.Y - m1*A1.X;
	float b2 = A2.Y - m2*A2.X;

	FVector P;
	P.X = (b2 - b1) / (m1 - m2);
	P.Y = m1*P.X + b1;
	P.Z = A1.Z;

	FInterpCurveVector Curve;

	Curve.AddPoint(0.0f, B1);
	Curve.AddPoint(0.5f, P);
	Curve.AddPoint(1.0f, B2);

	SplineTurn->spl->ClearSplinePoints();


	for (float i = 0.0f; i <= 1.0f; i += 0.5f)
	{
		FVector CurvePoint = Curve.Eval(i);
		SplineTurn->spl->AddSplinePoint(CurvePoint, ESplineCoordinateSpace::World);
		//UE_LOG(LogTemp, Warning,TEXT("%f %f"), CurvePoint.X, CurvePoint.Y);
	}

	return SplineTurn;
}