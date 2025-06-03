#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFBuildingBase.generated.h"

UCLASS()
class FALLGUYSURVIVAL_API ATFBuildingBase : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BuildingInteriorVolume;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<class ATFBuildingOpening*> ExteriorOpenings;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<class ATFCharacter*> ActorsInside;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CurrentSealState = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float SealValuePerPortal = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ClampMin = 0, ClampMax = 50))
	float BuildingInsulationValue = 10.0f;

	UFUNCTION()
	void OnInteriorZoneOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnInteriorZoneOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyindex);

protected:

	virtual void BeginPlay() override;
	void OnConstruction(const FTransform& Transform) override;

public:	

	ATFBuildingBase();

	void RecalculateSeal();
};
