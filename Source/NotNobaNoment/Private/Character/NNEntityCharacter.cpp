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

    InitEventComponent<ANNEntityCharacter>(this);
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
void ANNEntityCharacter::Move(FVector Direction)
{
    if (!Controller) return; // Vérification de validité du contrôleur

    // Si c'est un joueur
    if (Controller->IsA(APlayerController::StaticClass()))
    {
        //LOG
        UE_LOG(LogTemp, Warning, TEXT("Move"));
        //LOG des vecteurs
        UE_LOG(LogTemp, Warning, TEXT("Direction : %s"), *Direction.ToString());

        AddMovementInput(Direction.RightVector, 1.5f);
        AddMovementInput(Direction.ForwardVector, 1.5f);
    }
    else // Si c'est une IA
    {
       /* AAIController* AIController = Cast<AAIController>(GetController());
        if (AIController)
        {
            AIController->MoveToLocation(GetActorLocation() + Direction * 100.0f);
        }*/
    }
}

void ANNEntityCharacter::Look(FVector Direction)
{
    if (!Controller) return; // Vérification de validité du contrôleur
    // Si c'est un joueur
    if (Controller->IsA(APlayerController::StaticClass()))
    {
        AddControllerYawInput(Direction.X);
        AddControllerPitchInput(Direction.Y);
        //LOG
        UE_LOG(LogTemp, Warning, TEXT("Look"));
    }
    else // Si c'est une IA
    {
        /*AAIController* AIController = Cast<AAIController>(GetController());
        if (AIController)
        {
            AIController->MoveToLocation(GetActorLocation() + Direction * 100.0f);
        }*/
    }
}
