// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


TArray<FString> StringChop(FString Source, char split = '|')
{
	TArray<FString> Ret;
	FString Push;

	for(int i = 0; i < (int)Source.Len(); i++)
	{
		if (Source[i] == split)
		{
			Ret.Add(Push);
			Push.Empty();
		}
		else {
			Push += Source[i];
			if (i == Source.Len())
			{
				Ret.Add(Push);
			}
		}
	}
	return Ret;
}
