// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFBuildingOpening.h"

void ATFBuildingOpening::SetParent(const ATFBuildingBase* ParentBuilding)
{

}

bool ATFBuildingOpening::GetIsClosed() const
{
	return false;
}

FText ATFBuildingOpening::GetInteractionText_Implementation()
{
	return FText();
}
