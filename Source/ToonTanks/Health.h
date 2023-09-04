// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Variable",meta= (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;
	float NormalHealth = 0.f;	

// this is the function that will be called when the health is changed , it takes DamageActor as a parameter and Damage amount 
//, DamageType for the type of damage ,
 //InstigatedBy for the controller that instigated the damage and DamageCauser for the actor that caused the damage
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	class AToonTanksGameMode* ToonTanksGameMode;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
