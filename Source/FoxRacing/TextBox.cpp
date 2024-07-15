// Fill out your copyright notice in the Description page of Project Settings.

#include "TextBox.h"
#include "FoxRacing/LessonExercises.h"
#include <cmath>

// Sets default values
ATextBox::ATextBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
// Called when the game starts or when spawned
void ATextBox::BeginPlay()
{
	Super::BeginPlay();
	startTime = GetWorld()->GetTimeSeconds();
}

// Called every frame
void ATextBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	timer += DeltaTime;
	if (timer >= 0.2f)
	{
		sec += timer; timer = 0;
		CPM = (charTyped * 60) / sec;
		WPM = CPM / 5;
		if (correct + wrong > 0) WPM *= (correct / (correct + wrong));
		/*GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%f"), GetWorld()->GetTimeSeconds() - startTime));*/

	}

	if (stop) return;
	timer2 += DeltaTime;
	if (timer2 >= 4.f)
	{
		double CPMI = charTypedInst * 15;
		double WPMI = CPMI / 5;
		if (abs(WPM - WPMI) > 30)
		{
			charTyped = charTypedInst;
			sec = timer;
		}
		timer2 = 0;
		charTypedInst = 0;
	}
}

void ATextBox::Reset()
{
	stop = 1;
	charTyped = charTypedInst = 0;
	sec = 0;
}

int32 ATextBox::WpmLow()
{
	if (WPM < 20) return 0;
	if (WPM < 60) return 20;
	if (WPM < 80) return 60;
	if (WPM < 100) return 80;
	if (WPM < 150) return 100;
	if (WPM < 200) return 150;
	if (WPM < 250) return 200;
	return 250;
}

int32 ATextBox::WpmHigh()
{
	if (WPM < 20) return 20;
	if (WPM < 60) return 60;
	if (WPM < 80) return 80;
	if (WPM < 100) return 100;
	if (WPM < 150) return 150;
	if (WPM < 200) return 200;
	if (WPM < 250) return 250;
	return 300;
}

int32 ATextBox::WpmToAngle(double val)
{
	if (val == 0) return -120;
	if (val == 20) return -88;
	if (val == 60) return -56;
	if (val == 80) return -28;
	if (val == 100) return 0;
	if (val == 150) return 25;
	if (val == 200) return 55;
	if (val == 250) return 88;
	return 124;
}

FString ATextBox::GetWord()
{
	int32 lesson = rand() % std::max(knowledge + 1, 1);
	if (lesson == COMMA || lesson == DIGITS)
		return GetWord();

	FLessons* Row = DT_RandomWords->FindRow<FLessons>(FName(FString::FromInt(rand() % wordCount[lesson] + 1)), "");
	FString Word;
	switch (lesson)
	{
	case HOME:
		Word = Row->HOME;
		break;
	case EI:
		Word = Row->EI;
		break;
	case RU:
		Word = Row->RU;
		break;
	case WO:
		Word = Row->WO;
		break;
	case CN:
		Word = Row->CN;
		break;
	case VM:
		Word = Row->VM;
		break;
	case TY:
		Word = Row->TY;
		break;
	case GH:
		Word = Row->GH;
		break;
	case QP:
		Word = Row->QP;
		break;
	case XB:
		Word = Row->XB;
		break;
	case Z:
		Word = Row->Z;
		break;
	case DIGITS:
		Word = Row->DIGITS;
		break;
	}

	return Word;
}

FString ATextBox::SetText()
{
	if (Mode == LESSON)
	{
		mistakes += crtmistakes; crtmistakes = 0;
		exCountercrt += counter + 1; counter = 0;
		FString leftmax = Exercises.Left(maxchar);
		int32 pos = 0;
		leftmax.FindLastChar(' ', pos);
		CrtExerciseString = Exercises.Left(pos+1);
		Exercises = Exercises.RightChop(pos+1);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, CrtExerciseString);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Exercises);
		return CrtExerciseString;
	}

	freeRoamText.Empty();
	int32 charcounter = 0;
	FString Word = GetWord();
	for (charcounter = Word.Len() + 1; charcounter <= maxchar; charcounter += Word.Len() + 1)
	{
		freeRoamText += Word; freeRoamText.AppendChar(' ');
		Word = GetWord();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, freeRoamText);
	return freeRoamText;
}

FString ATextBox::GetKeyName(char key)
{
	if (key == '`' || key == '~') return "Backtick";
	if (key == '!') return "1";
	if (key == '@') return "2";
	if (key == '#') return "3";
	if (key == '$') return "4";
	if (key == '%') return "5";
	if (key == '^') return "6";
	if (key == '&') return "7";
	if (key == '*') return "8";
	if (key == '(') return "9";
	if (key == ')') return "0";
	if (key == '_') return "-";
	if (key == '+' || key == '=') return "Equal";

	if (key == '[' || key == '{') return "LSquare";
	if (key == ']' || key == '}') return "RSquare";
	if (key == '\\' || key == '|') return "Backslash";

	if (key == ';' || key == ':') return "Semicolon";
	if (key == '\'' || key == '\"') return "Apostrophe";

	if (key == '<' || key == ',') return "Comma";
	if (key == '.' || key == '>') return "Dot";
	if (key == '?' || key == '/') return "Slash";

	if (key == ' ') return "Space";
	if (key >= 'a' && key <= 'z') key = key - 'a' + 'A';

	FString rez;
	rez.AppendChar(key);
	return rez;
}

void ATextBox::SetFingers(char c)
{
	if (c == ' ') 
		if (lfinger != 0)
		{
			rfinger = 1; lfinger = 0;
			return;
		}
		else
			{
				lfinger = 1; rfinger = 0;
				return;
			}
	char* leftchar = "asdfgqwertzxcvb12345";
	lfinger = rfinger = 0;
	char copyc = c;
	if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
	if (strchr(leftchar, c))
	{
		char* f2 = "fgvbrt45";
		char* f3 = "dce3";
		char* f4 = "sw2x";
		char* f5 = "aq1z";
		char* shift = "!@#$%^";

		if (strchr(f2, c)) lfinger = 2;
		else
			if (strchr(f3, c)) lfinger = 3;
			else
				if (strchr(f4, c)) lfinger = 4;
				else
					lfinger = 5;
		if ((copyc >= 'A' && copyc <= 'Z') || strchr(shift, c))
		{
			rfinger = 5; 
			ColorKey("RShift");
		}
		return;
	}

	char* f2 = "jhuynm67";
	char* f3 = "ki,8<";
	char* f4 = "lo9.>";
	char* f5 = "\':\";[]-=0/[?]";
	char* shift = "\":<>?{}_+&*()";
	if (strchr(f2, c)) rfinger = 2;
	else
		if (strchr(f3, c)) rfinger = 3;
		else
			if (strchr(f4, c)) rfinger = 4;
			else
				rfinger = 5;
	if ((copyc >= 'A' && copyc <= 'Z') || strchr(shift, c))
	{
		lfinger = 5;
		ColorKey("LShift");
	}
}


int32 ATextBox::GetFingerPosX(bool hand, int32 finger)
{
	int32 rez;
	if (hand)
	{
		switch (finger)
		{
		case 1:
			rez = 1628;
			break;
		case 2:
			rez = 1628;
			break;
		case 3:
			rez = 1656;
			break;
		case 4:
			rez = 1696;
			break;
		case 5:
			rez = 1740;
			break;
		}
		return rez;
	}

	switch (finger)
	{
	case 1:
		rez = 456;
		break;
	case 2:
		rez = 448;
		break;
	case 3:
		rez = 420;
		break;
	case 4:
		rez = 384;
		break;
	case 5:
		rez = 340;
		break;
	}
	return rez;
}

int32 ATextBox::GetFingerPosY(bool hand, int32 finger)
{
	int32 rez;
	if (hand)
	{
		switch (finger)
		{
		case 1:
			rez = 832;
			break;
		case 2:
			rez = 684;
			break;
		case 3:
			rez = 652;
			break;
		case 4:
			rez = 644;
			break;
		case 5:
			rez = 652;
			break;
		}
		return rez;
	}

	switch (finger)
	{
	case 1:
		rez = 832;
		break;
	case 2:
		rez = 684;
		break;
	case 3:
		rez = 656;
		break;
	case 4:
		rez = 648;
		break;
	case 5:
		rez = 652;
		break;
	}
	return rez;
}

void ATextBox::FormatText()
{
	if (stop) return;
	FString StringToWrite;

	if (Mode == LESSON)
		StringToWrite = CrtExerciseString;
	else
		StringToWrite = freeRoamText;

		if (Input.Len() >= StringToWrite.Len())
		{

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, freeRoamText);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Input);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%d %d"), Input.Len(), freeRoamText.Len()));
			ResetInput();
			StringToWrite = SetText();
		}

	if (Mode == LESSON && StringToWrite.IsEmpty())
	{
		FinishLesson();
		return;
	}

	counter = 0;
	for (int32 i = 0; i < Input.Len(); ++i)
	{
		FString c = StringToWrite.Mid(i, 1);
		if (c.Equals(" ")) counter++;
	}

	char* SInput = TCHAR_TO_ANSI(*Input);
	std::string SOutput;
	char* SText = TCHAR_TO_ANSI(*StringToWrite);
	std::string aux; bool equal = 0;
	bool ok = 1; int i = 0;

	if (!SInput[0])
	{
		ProgressBarColor = DEFAULT;
		WPMCounterColor = WPMCORRECT;

		SOutput += "<Selected>";
		SOutput += SText[0];
		SOutput += "</>";

		if (Mode == LESSON)
		{
			ResetKeys();
			SetFingers(SText[i]);
			FString Key = GetKeyName(SText[i]);
			ColorKey(Key);
		}

		SOutput += SText + 1;

		Output = FString(UTF8_TO_TCHAR(SOutput.c_str()));
		return;
	}

	charTyped++;
	charTypedInst++;

	correct = wrong = 0;

	crtmistakes = 0;
	for (i = 0; SInput[i]; ++i)
		if (SInput[i] != SText[i]) crtmistakes++;

	ok = 1;
	for (i = 0; SInput[i]; ++i)
	{
		if (SText[i] == ' ')
		{
			if (ok) correct++;
			else
				wrong++;

			ok = 1;
			continue;
		}

		if (SInput[i] != SText[i]) ok = 0;
	}

	if (!SText[i])
		if (ok) correct++;
		else
			wrong++;

	if (SInput[0] == SText[0])
		aux = "<Correct>", equal = 1;
	else
		aux = "<Wrong>", equal = 0;


	SOutput += aux;
	SOutput += SInput[0];

	for (i = 1; SInput[i] && (SInput[i] == SText[i]) == equal; ++i)
		SOutput += SInput[i];

	for (; SInput[i]; ++i)
	{
		SOutput += "</>";

		if (SInput[i] == SText[i])
			aux = "<Correct>", equal = 1;
		else
			aux = "<Wrong>", equal = 0;

		SOutput += aux;
		for (i; SInput[i] && (SInput[i] == SText[i]) == equal; ++i)
			SOutput += SInput[i];

		i--;
	}


	if (SInput[i - 1] == SText[i - 1])
		ProgressBarColor = CORRECT, WPMCounterColor = WPMCORRECT;
	else
		ProgressBarColor = WRONG, WPMCounterColor = WPMWRONG;


	SOutput += "</>";

	if (SText[i])
	{
		SOutput += "<Selected>";
		SOutput += SText[i];
		SOutput += "</>";
		if (Mode == LESSON)
		{
			ResetKeys();
			SetFingers(SText[i]);
			FString Key = GetKeyName(SText[i]);
			ColorKey(Key);
		}
	}

	SOutput += SText + i + (SText[i] != NULL);

	Output = FString(UTF8_TO_TCHAR(SOutput.c_str()));
}