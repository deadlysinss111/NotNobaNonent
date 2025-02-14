// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NNArcherCharacter.h"

// Sets default values
ANNArcherCharacter::ANNArcherCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANNArcherCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANNArcherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANNArcherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

