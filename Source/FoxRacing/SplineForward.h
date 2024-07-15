// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spline.h"
#include "SplineForward.generated.h"

struct FInterpCurveVector;
class USplineComponent;

UCLASS()
class FOXRACING_API ASplineForward : public ASpline
{
	GENERATED_BODY()

	struct Point { double x, y; };


public:
	ASplineForward();

	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool reverse = 0;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* spl;

	UFUNCTION(BlueprintCallable)
	ASplineForward* GetSpline(int32 SplineID);

	UFUNCTION(BlueprintCallable)
	int32 GetIDAtDir(bool Dir);

	UFUNCTION(BlueprintCallable)
	ASplineTurn* GetSplineTurn(int32 a, int32 b);

	UFUNCTION(BlueprintCallable)
	ASplineTurn* CreateSplineTurn(int32 a, int32 b);
};
