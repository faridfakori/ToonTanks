// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	

public :

ATower();

virtual void Tick(float DeltaTime) override;

protected :

virtual void BeginPlay() override;

UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Variable",meta= (AllowPrivateAccess = "true"))
float FireRange = 500.f;

private :

class ATank* PlayerTank;


};
