// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTankEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTankEnemy::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTankEnemy::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTankEnemy::HandleDestruction() 
{
    Super::HandleDestruction();
    Destroy();
}


// Called every frame
void APawnTankEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
    {
        return;
    }

    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTankEnemy::CheckFireCondition() 
{
    // If Player == null || is Dead then Bail
    if(!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
    {
        return;
    }
    // If Player IS in range then Fire
    if(ReturnDistanceToPlayer() <= FireRange)
    {
        Fire();
    }
}

float APawnTankEnemy::ReturnDistanceToPlayer() 
{
    if(!PlayerPawn)
    {
        return 0.0f;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}