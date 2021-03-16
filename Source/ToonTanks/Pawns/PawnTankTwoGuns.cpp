// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTankTwoGuns.h"
#include "ToonTanks/Actors/ProjectileBase.h"

APawnTankTwoGuns::APawnTankTwoGuns()
{
    SecondProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Second Projectile Spawn Point"));
	SecondProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void APawnTankTwoGuns::BeginPlay() 
{
    Super::BeginPlay();
}

void APawnTankTwoGuns::Fire() 
{
    Super::Fire();
    
    // Fire second gun
    if(ProjectileClass)
	{
		FVector SpawnPoint = SecondProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = SecondProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnPoint, SpawnRotation);
		Projectile->SetOwner(this);
	}
}
