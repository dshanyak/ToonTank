// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnTank.h"
#include "PawnTankTwoGuns.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTankTwoGuns : public APawnTank
{
	GENERATED_BODY()

private:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SecondProjectileSpawnPoint;

public:
	APawnTankTwoGuns();

	virtual void BeginPlay() override;

	virtual void Fire() override;
	
};
