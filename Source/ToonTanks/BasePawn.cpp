// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Projectile.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("Capsule Collider");
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Projectile Spawn Point");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
	



}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{

	FVector ToTarget = LookAtTarget-TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f,ToTarget.Rotation().Yaw,0.f);
	FRotator LookAtRotationSmoothly = FMath::RInterpTo(TurretMesh->GetComponentRotation(),LookAtRotation,GetWorld()->DeltaTimeSeconds,5.f);
	TurretMesh->SetWorldRotation(LookAtRotationSmoothly);
	

	// LookAtRotation.Pitch = .f;
	// LookAtRotation.Roll = .f;

}

void ABasePawn::Fire()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileSpawnPointRotation = ProjectileSpawnPoint->GetComponentRotation();

	DrawDebugSphere(GetWorld(),ProjectileSpawnPointLocation,10.f,12,FColor::Red,false,3.f);

	GetWorld()->SpawnActor<AProjectile>(ProjectileClass,ProjectileSpawnPointLocation,ProjectileSpawnPointRotation);
}

