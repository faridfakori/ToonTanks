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
    PlayerInputComponent->BindAxis("Turn",this,&ATank::Turn);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

  PlayerControllerRef = Cast<APlayerController>(GetController());




}


// Called every frame
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


  if(PlayerControllerRef)
  
  {

    PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
    

     RotateTurret(HitResult.ImpactPoint);
     
     DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,20.f,12,FColor::Red,false,-1.f);

  }

  

}