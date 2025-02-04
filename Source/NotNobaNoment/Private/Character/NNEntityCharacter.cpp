// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NNEntityCharacter.h"

// Sets default values
ANNEntityCharacter::ANNEntityCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerComponent = CreateDefaultSubobject<UNNTriggerComponent>(TEXT("TriggerComponent"));
	HealthComponent = CreateDefaultSubobject<UNNHealthComponent>(TEXT("HealthComponent"));

	InitSmth<ANNEntityCharacter>(this);
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

// Called to bind functionality to input
void ANNEntityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

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
