// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);


}

void ATank::BeginPlay()
{

	 Super::BeginPlay();


   TankPlayerController = Cast<APlayerController>(GetController());

}

void ATank::HandleDestruction()
{

  Super::HandleDestuction();

   
  // Hide all components
  SetActorHiddenInGame(true);
  // -- Or just call base pawn hide function
  // Delete self
  SetActorTickEnabled(false);

}



void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	  Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward",this,&ATank::Move);

    PlayerInputComponent->BindAxis("Turn",this,&ATank::Turn);

    PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&ATank::Fire);

}


void ATank::Move(float Value)

{

 FVector DeltaLocation = FVector::ZeroVector;

 DeltaLocation.X = Value * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

 AddActorLocalOffset(DeltaLocation,true);

}

void ATank::Turn(float Value)

{

 FRotator DeltaRotation = FRotator::ZeroRotator;

 DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);

 AddActorLocalRotation(DeltaRotation,true);

}



void ATank::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

  FHitResult HitResult;

  if(TankPlayerController)  
  {

     TankPlayerController->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
    
     RotateTurret(HitResult.ImpactPoint);
     
     DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,20.f,12,FColor::Red,false,-1.f);

  }

}