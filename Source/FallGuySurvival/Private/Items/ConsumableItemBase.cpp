// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ConsumableItemBase.h"
#include "BaseClass/TFCharacter.h"

void UConsumableItemBase::OnUse(ATFCharacter* Caller)
{
	UStatlineComponent* statline = Caller->GetStatline();
	for (TPair<ECoreStat, float>& affect : StatAdjustments)
	{
		statline->AdjustStat(affect.Key, affect.Value);
	}
}
