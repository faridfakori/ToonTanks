// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Tank.h"

ATower::ATower()
{
    
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (InFireRange())
    {
        RotateTurret(PlayerTank->GetActorLocation());
    }
    
  
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    
    PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle,this,&ATower::CheckFireCondition,FireRate,true);
}



void ATower::CheckFireCondition()
{
    if (InFireRange())
    {
        Fire();
    }
    
}

bool ATower::InFireRange()
{

    if(PlayerTank)
    {
         float Distance = FVector::Dist(GetActorLocation(),PlayerTank->GetActorLocation());

       if (Distance <= FireRange)
        {

            return true;
            
        }
    
    }
    return false;
}
