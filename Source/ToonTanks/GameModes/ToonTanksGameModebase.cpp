// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameModebase.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"


void AToonTanksGameModebase::BeginPlay() 
{
    Super::BeginPlay();

    HandleGameStart();
}


void AToonTanksGameModebase::ActorDied(AActor* DeadActor) 
{
    // Check what actor died. If turret, tally score. If player, go to lose condition
    if(DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);

        // remove input functionality
        if(PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
    }
    else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction(); // destroy the turret
        TurretCount--; // one less turret in game

        // if no more turrets, end game with win condition
        if(TurretCount <=0)
        {
            HandleGameOver(true);
        }
    }

}

void AToonTanksGameModebase::HandleGameStart() 
{
    TurretCount = GetTurretCount();  // get the starting number of turrets in the game
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

    GameStart(); // calls blueprint methods

    if(PlayerControllerRef)
    {
        // start game with no player input funcitonality
        PlayerControllerRef->SetPlayerEnabledState(false);

        // after delay, allow user input functionality
        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelgate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelgate, StartDelay, false);
    }

}

void AToonTanksGameModebase::HandleGameOver(bool PlayerWon) 
{
    GameOver(PlayerWon); // Calls blueprint method
    

}

int32 AToonTanksGameModebase::GetTurretCount() 
{
    // Get the number of turrets in the level
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return TurretActors.Num();
}

