// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotTextBox.h"
#include "GameProgress.h"
#include "FoxRacing/LessonScript.h"
#include "FoxRacing/LessonScriptRO.h"

// Sets default values
ARobotTextBox::ARobotTextBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARobotTextBox::BeginPlay()
{
	Super::BeginPlay();
}

void ARobotTextBox::ApplyLessonScript()
{
	UGameProgress* GameInstance = Cast<UGameProgress>(GetGameInstance());
	if (GameInstance)
	{
		bool lang = GameInstance->Lang;
		if (lang)
		{
			Script.SetNum(ScriptEng.Num());
			for (int32 i = 0; i < ScriptEng.Num(); ++i)
				Script[i] = ScriptEng[i];
		}
		else
		{
			Script.SetNum(ScriptRo.Num());
			for (int32 i = 0; i < ScriptRo.Num(); ++i)
				Script[i] = ScriptRo[i];
		}
	}
}

// Called every frame
void ARobotTextBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	timer++;
	if (timer > 1 / (DeltaTime * printSpeed))
	{
		timer = 0;
		if (pos <= text.Len())
		{
			FString c = text.Mid(pos - 1, 1);
			if (c.Equals(TEXT("<")))
			{
				change = 1;
				Tag.Empty();
				int32 i;
				for (i = pos - 1; i < text.Len(); ++i)
				{
					FString currChar = text.Mid(i, 1);
					Tag += currChar;
					if (currChar.Equals(">"))
						break;
				}
				pos = i + 1;
			}

			Output = text.Left(pos);
			if (change)
			{
				Output.Append("</>");
				FString currChar = text.Mid(pos, 3);
				if (currChar.Equals("</>"))
				{
					pos += 3;
					change = 0;
				}
			}
			pos++;
		}
		else
			{
				if (!Input.IsEmpty())
					Print2(Input);
				else
					if (scriptIndex < Script.Num()-1)
						Enter1();
			}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString(Input));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Output);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Script[scriptIndex]);
}

void ARobotTextBox::Print()
{
	Enter0();
	finishedPrinting = 0;
	pos = 1; change = 0;
	Output.Empty();
	Input = Script[scriptIndex]; Output = 0;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString(Input));
	if (Input.Len() < maxChar) 
		text = Input, Input.Empty();
	else
		{
			int32 nr = 0;
			text = Input.Left(maxChar);
			text.FindLastChar(' ', nr);
			text = text.Left(nr);

			Input = Input.RightChop(nr+1);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString(Input));
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString(text));
		}
	if (change)
	{
		FString copy = text;
		text.Empty();
		text += Tag;
		text += copy;
	}
}

void ARobotTextBox::Print2(FString String)
{
	finishedPrinting = 0;
	pos = 1;
	Output.Empty();
	Input = String; Output = 0;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString(Input));
	if (Input.Len() < maxChar) 
		text = Input, Input.Empty();
	else
		{
			int32 nr = 0;
			text = Input.Left(maxChar);
			text.FindLastChar(' ', nr);
			text = text.Left(nr);

			Input = Input.RightChop(nr+1);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString(Input));
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString(text));
		}
	if (change)
	{
		FString copy = text;
		text.Empty();
		text += Tag;
		text += copy;
	}
}
