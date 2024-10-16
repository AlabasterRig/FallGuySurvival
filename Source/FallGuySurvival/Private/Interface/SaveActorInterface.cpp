// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/SaveActorInterface.h"

// Add default functionality here for any ISaveActorInterface functions that are not pure virtual.

FGuid ISaveActorInterface::GetActorSaveID_Implementation()
{
    FGuid Ret = FGuid();
    Ret.Invalidate();
    return Ret;
}

void ISaveActorInterface::SetActorGuid_Implementation(const FGuid& NewGuid)
{

}

FSaveActorData ISaveActorInterface::GetSaveData_Implementation()
{
    return FSaveActorData();
}

void ISaveActorInterface::UpdateFromSave_Implementation()
{
    // UpdateFromSave();
}

FSaveComponentsData ISaveActorInterface::GetComponentSaveData_Implementation()
{
    return FSaveComponentsData();
}

void ISaveActorInterface::SetComponentSaveData_Implementation(FSaveComponentsData Data)
{

}

void ISaveActorInterface::SetActorRawSaveData_Implementation(const TArray<FString>& Data)
{
}
