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
}

void ANNPlayerCharacter::Tick(float DeltaTime)
{
}

// Called to bind functionality to input
void ANNPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::HandlePlayerInputMove);
        Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::HandlePlayerLook);

        //OTHER ACTION
		UE_LOG(LogTemp, Warning, TEXT("PlayerInputComponent is UEnhancedInputComponent"));
    }
    else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInputComponent is not UEnhancedInputComponent"));
	}
}

void ANNPlayerCharacter::HandlePlayerInputMove(const FInputActionValue& InputValue)
{
    FVector2D Movement = InputValue.Get<FVector2D>();
    Move(FVector(Movement.X, Movement.Y, 0));
}


void ANNPlayerCharacter::HandlePlayerLook(const FInputActionValue& InputValue)
{
	FVector2D Movement = InputValue.Get<FVector2D>();
	Look(FVector(Movement.X, Movement.Y, 0));
}
