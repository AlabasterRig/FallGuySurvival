// Fill out your copyright notice in the Description page of Project Settings.


#include "TF_Utils.h"

TArray<FString> StringChop(FString Source, char split)
{
	TArray<FString> Ret;
	FString Push;
	for (int i = 0; i < (int)Source.Len(); i++)
	{
		if (Source[i] == split)
		{
			Ret.Add(Push);
			Push.Empty();
		}
		else
		{
			Push += Source[i];
			if (i == ((int)Source.Len() - 1))
			{
				Ret.Add(Push);
			}
		}
	}
	return Ret;
}
