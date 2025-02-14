// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/NNEntityCharacter.h"

// Sets default values
ANNEntityCharacter::ANNEntityCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<UNNCollisionComponent>(TEXT("CollisionComponent"));
    HealthComponent = CreateDefaultSubobject<UNNHealthComponent>(TEXT("HealthComponent"));
    AbilityComponent = CreateDefaultSubobject<UNNAbility>(TEXT("AbilityComponent"));

    InitEventComponent<ANNEntityCharacter>(this);
}

// Called when the game starts or when spawned
void ANNEntityCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ANNEntityCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ANNEntityCharacter::OnHealthChanged(float CurrentHealth)
{
    //LOG
	UE_LOG(LogTemp, Warning, TEXT("Health changed to: %f"), CurrentHealth);
}