// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	NormalHealth = MaxHealth;

	// what this does is that it adds a dynamic function to the OnTakeAnyDamage event of the owner of this component
	GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UHealth::DamageTaken);
	// ...
	ToonTanksGameMode = Cast<AToonTanksGameMode>(GetWorld()->GetAuthGameMode());
	
}

void UHealth::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,  AController* InstigatedBy, AActor* DamageCauser)
{

	if (Damage <= 0 )//|| NormalHealth <= 0)
	{
		return;
	}
	NormalHealth -= Damage;
	UE_LOG(LogTemp,Warning,TEXT("Health is %f"),NormalHealth);

	if (NormalHealth <=0.f && ToonTanksGameMode)
	{
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
	


	
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

