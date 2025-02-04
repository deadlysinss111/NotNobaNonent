// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/NNEntity.h"

// Sets default values
ANNEntity::ANNEntity()
{
	TriggerComponent = CreateDefaultSubobject<UNNTriggerComponent>(TEXT("TriggerComponent"));

	// Set the event to call when an actor enters the trigger
	TriggerComponent->OnActorEnter.AddDynamic(this, &ANNEntity::OnActorEnter);
	// Set the event to call when an actor exits the trigger
	TriggerComponent->OnActorExit.AddDynamic(this, &ANNEntity::OnActorExit);

	HealthComponent = CreateDefaultSubobject<UNNHealthComponent>(TEXT("HealthComponent"));
	
	// Set the event to call when the health of the entity changes
	HealthComponent->OnHealthChanged.AddDynamic(this, &ANNEntity::OnHealthChanged);
	// Set the event to call when the entity dies
	HealthComponent->OnDeath.AddDynamic(this, &ANNEntity::OnDeath);
}

void ANNEntity::OnActorEnter(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor entered the trigger"));
}

void ANNEntity::OnActorExit(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor exited the trigger"));
}

void ANNEntity::OnHealthChanged(float CurrentHealth)
{
	UE_LOG(LogTemp, Warning, TEXT("Health changed: %f"), CurrentHealth);
}

void ANNEntity::OnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Entity died"));
}

// Called when the game starts or when spawned
void ANNEntity::BeginPlay()
{
	Super::BeginPlay();
	
}