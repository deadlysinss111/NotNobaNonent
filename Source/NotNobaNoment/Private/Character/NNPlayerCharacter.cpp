// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NNPlayerCharacter.h"
#include <EnhancedInputComponent.h>
#include "Camera/CameraComponent.h"

ANNPlayerCharacter::ANNPlayerCharacter()
{
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(RootComponent);
    Camera->bUsePawnControlRotation = true;
}

void ANNPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ANNPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANNPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::HandlePlayerInputMove);
        Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::HandlePlayerLook);
    }
}

void ANNPlayerCharacter::HandlePlayerInputMove(const FInputActionValue& InputValue)
{
    FVector2D Movement = InputValue.Get<FVector2D>();
   
    //LOG
    UE_LOG(LogTemp, Warning, TEXT("Move"));
    //LOG des vecteurs
    UE_LOG(LogTemp, Warning, TEXT("Direction : %s"), *Movement.ToString());

    //Move
	AddMovementInput(FVector(Movement.Y, Movement.X, 0));
}


void ANNPlayerCharacter::HandlePlayerLook(const FInputActionValue& InputValue)
{
    FVector2D Movement = InputValue.Get<FVector2D>();
    AddControllerYawInput(Movement.X);
    AddControllerPitchInput(Movement.Y);
}
