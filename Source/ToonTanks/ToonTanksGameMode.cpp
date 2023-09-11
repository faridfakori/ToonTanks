// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
   if (DeadActor == Tank)
   {
        Tank->HandleDestruction();

        if (ToonTankPlayerController)
        {
              ToonTankPlayerController->SetPlayerEnabledState(false);
        }
   }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))    
    {
        DestroyedTower->HandleDestruction();
    }
   
}


void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    HandleGameStart();

}

void AToonTanksGameMode::HandleGameStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

    ToonTankPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));

    StartGame();

    FTimerDelegate PlayerEnableTimeDelegate = FTimerDelegate::CreateUObject(ToonTankPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);

    if (ToonTankPlayerController)
    {
        ToonTankPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;

        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,PlayerEnableTimeDelegate, StartDelay, false);
    }
}