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
// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Super::SetupPlayerInputComponent(PlayerInputComponent);

  // Bind Axis
    PlayerInputComponent->BindAxis("MoveForward",this,&ATank::Move);
}


// Called every frame
   void ATank::Move(float Value)

{
//   UE_LOG(LogTemp,Warning,TEXT("Move Forward : %f"),Value);


  FVector DeltaLocation = FVector::ZeroVector;


// Determine direction based on input
  DeltaLocation.X = Value * MoveSpeed * GameplayStatics::GetWorldDeltaSeconds(this);


// Move based on direction
  AddActorLocalOffset(DeltaLocation);

  
// Call parent implementation
    UE_LOG(LogTemp,Warning,TEXT("Value : %f"),Value);

}
