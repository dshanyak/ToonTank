// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
    SetupTimerLoop();

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

void APawnTurret::HandleDestruction() 
{
    Super::HandleDestruction();
    Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(!PlayerPawn || GetDistanceToPlayer() > MaxFireDistance)
    {
        return;
    }
    
    RotateTurret(PlayerPawn->GetActorLocation());
    
}

void APawnTurret::CheckFireCondition()
{
    // If player == null || dead, then bail
    if(!PlayerPawn)
    {
        return;
    }

    // if player IS in range, fire
    if(GetDistanceToPlayer() <= MaxFireDistance && PlayerPawn->GetIsPlayerAlive())
    {
        Fire();
    }

}

float APawnTurret::GetDistanceToPlayer()
{
    // If player == null || dead, then bail
    if(!PlayerPawn)
    {
        return MaxFireDistance+1;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());

}

void APawnTurret::SetupTimerLoop()
{
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

