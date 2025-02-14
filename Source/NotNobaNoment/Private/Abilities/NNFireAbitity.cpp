// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/NNFireAbitity.h"

void UNNFireAbitity::Trigger(KeyState state)
{
	//LOG
	UE_LOG(LogTemp, Warning, TEXT("GOOOOOO"));

    if (!_owner) return;

    Fire();

    _owner->GetWorldTimerManager().SetTimer(FireTimer, this, &UNNFireAbitity::Fire, FireRate, true);
}

void UNNFireAbitity::Fire()
{   
	if (!_target && _BPArrow) return;
    
	//Get a reference to the arrow in _BPArrow
	//Spawn the arrow at the turret's location to the direction of the target

	//Target direction
	FVector direction = _target->GetActorLocation() - _owner->GetActorLocation();

	//Get the object with tag spawnPoint in the owner component
    UActorComponent* component = _owner->FindComponentByTag(UActorComponent::StaticClass(), "spawnPoint");

	//LOG
	UE_LOG(LogTemp, Warning, TEXT("Fire"));

	if (USceneComponent* SceneComp = Cast<USceneComponent>(component))
	{
		//LOG
		

		UE_LOG(LogTemp, Warning, TEXT("Spawn"));
		//Spawn the arrow at the turret's location to the direction of the target
		GetWorld()->SpawnActor<AActor>(_BPArrow, SceneComp->GetComponentLocation(), direction.ToOrientationRotator());
	}
	else
	{
		//Log error
		UE_LOG(LogTemp, Warning, TEXT("No spawn point found"));
	}
}