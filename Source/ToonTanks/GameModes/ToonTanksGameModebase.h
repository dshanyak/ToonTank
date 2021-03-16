// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameModebase.generated.h"

// Forward declarations
class APawnTurret;
class APawnTank;
class APlayerControllerBase;


UCLASS()
class TOONTANKS_API AToonTanksGameModebase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	APawnTank* PlayerTank;
	int32 TurretCount = 0;
	APlayerControllerBase* PlayerControllerRef;

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
	int32 GetTurretCount();

	

public:
	void ActorDied(AActor* DeadActor);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 4;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);


};
