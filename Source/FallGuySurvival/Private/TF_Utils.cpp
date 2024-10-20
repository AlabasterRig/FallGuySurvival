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

int RandomIntFromVector(const ERandomizedVector& DirectionRandomization, const FVector& Location)
{
	switch (DirectionRandomization)
	{
	case ERandomizedVector::X:
		return floor(Location.X);
	case ERandomizedVector::Y:
		return floor(Location.Y);
	case ERandomizedVector::Z:
		return floor(Location.Z);
	case ERandomizedVector::XY:
		return floor(Location.X + Location.Y);
	case ERandomizedVector::XZ:
		return floor(Location.X + Location.Z);
	case ERandomizedVector::YZ:
		return floor(Location.Y + Location.Z);
	case ERandomizedVector::XYZ:
		return floor(Location.X + Location.Y + Location.Z);
	default:
		return 0;
	}
}
