// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterTank.h"
#include "Kismet/GameplayStatics.h"
#include "D:\DDownload\cs1c\ToonTank\Source\ToonTanks\Pawns\PawnTank.h"

// Called when the game starts or when spawned
void ACharacterTank::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ACharacterTank::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ACharacterTank::HandleDestruction() 
{
    Super::HandleDestruction();
    Destroy();
}

// Called every frame
void ACharacterTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
    {
        return;
    }

    RotateTurret(PlayerPawn->GetActorLocation());
}

void ACharacterTank::CheckFireCondition() 
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

float ACharacterTank::ReturnDistanceToPlayer() 
{
    if(!PlayerPawn)
    {
        return 0.0f;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
