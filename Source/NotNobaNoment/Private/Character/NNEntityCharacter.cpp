// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/NNEntityCharacter.h"



// Sets default values
ANNEntityCharacter::ANNEntityCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    TriggerComponent = CreateDefaultSubobject<UNNTriggerComponent>(TEXT("TriggerComponent"));
    HealthComponent = CreateDefaultSubobject<UNNHealthComponent>(TEXT("HealthComponent"));
	AbilityComponent = CreateDefaultSubobject<UNNAbility>(TEXT("AbilityComponent"));

    InitSmth<ANNEntityCharacter>(this);
}

// Called when the game starts or when spawned
void ANNEntityCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(GEngine != nullptr);

    // Display a debug message for five seconds. 
    // The -1 "Key" value argument prevents the message from being updated or refreshed.
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
}

// Called every frame
void ANNEntityCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


// Events
void ANNEntityCharacter::OnActorEnter(AActor* OtherActor)
{
}

void ANNEntityCharacter::OnActorExit(AActor* OtherActor)
{
}

void ANNEntityCharacter::OnHealthChanged(float CurrentHealth)
{
}

void ANNEntityCharacter::OnDeath()
{
}

// Functions

// Movement
void ANNEntityCharacter::Move()
{
    //LOG
	UE_LOG(LogTemp, Warning, TEXT("Move"));
   
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, 1.0f);

	Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, 1.0f);
}

void ANNEntityCharacter::Look()
{
}

