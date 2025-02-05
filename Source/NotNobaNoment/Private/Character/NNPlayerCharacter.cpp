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
        Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::Move);
        Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::Look);

        //OTHER ACTION
    }
}
