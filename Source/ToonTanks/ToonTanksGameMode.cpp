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
        GameOver(false);
   }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))    
    {
        DestroyedTower->HandleDestruction();
        --TargetTowers;

        if (TargetTowers == 0)
        {
            GameOver(true);
        }
        
    }
   
}


void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    HandleGameStart();

}

void AToonTanksGameMode::HandleGameStart()
{

    TargetTowers = GetTargetTowersCount();

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

int32 AToonTanksGameMode::GetTargetTowersCount()
{
    TArray<AActor*> Towers;

    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

    return Towers.Num();
}