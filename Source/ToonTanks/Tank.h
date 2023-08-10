// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public : 
// Sets default values for this pawn's properties
ATank();

// Called to bind functionality to input
virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected :

 private : 

		UPROPERTY(EditAnywhere , BlueprintReadOnly, Category = "Variables", meta = (AllowPrivateAccess = "true"))
		float MoveSpeed = 100.f;

		UPROPERTY(VisibleAnywhere  , Category = "Component" , meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

		UPROPERTY(VisibleAnywhere  , Category = "Component" , meta = (AllowPrivateAccess = "true")) 
		class USpringArmComponent* SpringArm;

		void Move(float Value);
 
};


