// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RobotTextBox.generated.h"

UCLASS()
class FOXRACING_API ARobotTextBox : public AActor
{
	GENERATED_BODY()

	int32 timer = 0;
	int32 printSpeed = 27;
	FString text; int32 pos = 0;
	const int32 maxChar = 300;
	FString Input;
	bool change = 0; FString Tag;
	enum Lessons : int
	{
		HOME = 0,
		EI = 1,
		RU = 2,
		WO = 3,
		CN = 4,
		COMMA = 5,
		VM = 6,
		TY = 7,
		GH = 8,
		QP = 9,
		XB = 10,
		Z = 11,
		DIGITS = 12,
	};


public:	
	// Sets default values for this actor's properties
	ARobotTextBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> Script;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> ScriptRo;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> ScriptEng;

	UPROPERTY(BlueprintReadWrite)
	int32 CrtLesson = 0;

	UFUNCTION(BlueprintCallable)
	void LessonScriptEng(int32 Lesson);

	UFUNCTION(BlueprintCallable)
	void LessonScriptRo(int32 Lesson);

	UFUNCTION(BlueprintCallable)
	void ApplyLessonScript();

	UPROPERTY(BlueprintReadWrite)
	FString Output;

	UPROPERTY(BlueprintReadWrite)
	bool finishedPrinting;

	UPROPERTY(BlueprintReadWrite)
	bool enter;

	UPROPERTY(BlueprintReadWrite)
	int32 scriptIndex = 0;

	UFUNCTION(BlueprintCallable)
	void Print();

	UFUNCTION(BlueprintImplementableEvent)
	void Enter1();

	UFUNCTION(BlueprintImplementableEvent)
	void Enter0();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateTextBox(int32 Lesson);

	UFUNCTION(BlueprintCallable)
	void Print2(FString String);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
