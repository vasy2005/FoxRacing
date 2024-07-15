// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameProgress.generated.h"

/**
 * 
 */
UCLASS()
class FOXRACING_API UGameProgress : public UGameInstance
{
	GENERATED_BODY()

public:
		UPROPERTY(BlueprintReadWrite)
		bool Lang = 0;
};
