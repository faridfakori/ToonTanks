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

	void HandleDestruction();

// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


 private : 

		UPROPERTY(EditAnywhere , BlueprintReadOnly, Category = "Variables", meta = (AllowPrivateAccess = "true"))
		float MoveSpeed = 1000.f;

		UPROPERTY(VisibleAnywhere  , Category = "Component" , meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

		UPROPERTY(VisibleAnywhere  , Category = "Component" , meta = (AllowPrivateAccess = "true")) 
		class USpringArmComponent* SpringArm;

		

		UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Variable",meta= (AllowPrivateAccess = "true"))
		float TurnRate = 100.f;



		void Move(float Value);
		void Turn(float Value);


		APlayerController* TankPlayerController;
};


