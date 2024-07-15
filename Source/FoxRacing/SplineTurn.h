// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spline.h"
#include "SplineTurn.generated.h"

class USplineComponent;
struct FInterpCurveVector;

UCLASS()
class FOXRACING_API ASplineTurn : public ASpline
{
	GENERATED_BODY()

public:
	ASplineTurn();

	virtual void Tick(float DeltaTime) override;

	USplineComponent* GetSpl();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* spl;

	bool isReady = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool reverse = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 a;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 b;

	UFUNCTION(BlueprintCallable)
	bool GetSplineForwardReverse();

protected:
	virtual void BeginPlay() override;



	UFUNCTION(BlueprintCallable)
	ASplineTurn* GetSpline(int32 Src, int32 Dest);

	UFUNCTION(BlueprintCallable)
	ASplineForward* GetSplineForward();


};
