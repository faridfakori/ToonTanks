// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

ATower::ATower()
{
    
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    
    PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if(PlayerTank)
    {
        float Distance = FVector::Dist(GetActorLocation(),PlayerTank->GetActorLocation()); 

        if (Distance <= FireRange)
        {
            Fire();
           
            RotateTurret(PlayerTank->GetActorLocation());

            
        }
        
    }
    
  
}