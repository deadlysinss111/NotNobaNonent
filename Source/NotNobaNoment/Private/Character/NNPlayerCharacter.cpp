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
    
    if (_abilitySet != NULL) {
        _attack = NewObject<UNNAbility>(this, _abilitySet->_attack);
        _attack->Init(this);
    }
    else
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("the ability set is null"));

    
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

        Input->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ANNPlayerCharacter::TriggerAttack);

        //OTHER ACTION
		UE_LOG(LogTemp, Warning, TEXT("PlayerInputComponent is UEnhancedInputComponent"));
    }
    else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInputComponent is not UEnhancedInputComponent"));
	}
}

void ANNPlayerCharacter::TriggerAttack() {
    _attack->Trigger();
}

void ANNPlayerCharacter::TriggerAbility_1() {
    _ability_1->Trigger();
}

void ANNPlayerCharacter::TriggerAbility_2() {
    _ability_2->Trigger();
}