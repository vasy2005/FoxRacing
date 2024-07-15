// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "TextBox.generated.h"

UCLASS()
class FOXRACING_API ATextBox : public AActor
{
	GENERATED_BODY()
	
	double timer = 0, timer2 = 0; double sec = 0; //second timer

	//keyboard
	int32 charTyped = 0, charTypedInst = 0;
	double correct = 0, wrong = 0;
	double wordCounter = 0;
	float smoothedWPM = 0.0f;
	const float alpha = 0.3f;
	double startTime = 0.0f;
	double elapsedTime = 0.0f;

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
		DIGITS = 12
	};

	int maxchar = 55;

	FString GetWord();

	//Modes
	enum Mode : int { FREEROAM = 2, CONTEST = 1, LESSON = 3 };

	//freeRoamWords
	FString freeRoamText;
	FString GetKeyName(char key);
	int32 wordCount[13] = { 24, 142, 190, 246, 868, 0, 765, 2092, 1912, 1586, 1182, 107, 0 };

	//LESSON
	FString CrtExerciseString;
	int32 maxMistakes = 20;
	void SetFingers(char);
	

	//CONTEST


public:
	// Sets default values for this actor's properties
	ATextBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int knowledge = HOME;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	const UDataTable* DT_RandomWords;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double WPM = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double CPM = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CrtLesson = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool exception = 0;

	UFUNCTION(BlueprintCallable)
	void LessonExercises(int32 Lesson);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ExerciseText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Exercises;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 exerciseIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool stop = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Input;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Output;

	UFUNCTION(BlueprintImplementableEvent)
	void FinishLesson();

	UPROPERTY(BlueprintReadWrite)
	int32 exCounter = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 exCountercrt = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 counter = -1;
	UPROPERTY(BlueprintReadWrite)
	int32 mistakes = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 crtmistakes = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 lfinger = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 rfinger = 0;
	UFUNCTION(BlueprintCallable)
	int32 GetFingerPosX(bool hand, int32 finger);
	UFUNCTION(BlueprintCallable)
	int32 GetFingerPosY(bool hand, int32 finger);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Mode = FREEROAM;

	UFUNCTION(BlueprintImplementableEvent)
	void ResetInput();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetKeys();

	UFUNCTION(BlueprintImplementableEvent)
	void ColorKey(const FString& Key);

	UFUNCTION(BlueprintCallable)
	FString SetText();

	UFUNCTION(BlueprintCallable)
	void FormatText();

	UFUNCTION(BlueprintCallable)
	int32 WpmLow();

	UFUNCTION(BlueprintCallable)
	int32 WpmHigh();

	UFUNCTION(BlueprintCallable)
	int32 WpmToAngle(double val);

	UFUNCTION(BlueprintCallable)
	void Reset();

	const FColor CORRECT = FColor::FromHex("#8FFFD077");
	const FColor DEFAULT = FColor::FromHex("9EA79D8F");
	const FColor WRONG = FColor::FromHex("FFB6B6A7");

	const FColor WPMCORRECT = FColor::FromHex("FFFFFFFF");
	const FColor WPMWRONG = FColor::FromHex("FF5764FF");

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FColor ProgressBarColor = DEFAULT;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FColor WPMCounterColor = WPMCORRECT;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

USTRUCT(BlueprintType)
struct FLessons : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString HOME;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString RU;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString WO;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CN;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString VM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString TY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString GH;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString QP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString XB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Z;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString DIGITS;
};
