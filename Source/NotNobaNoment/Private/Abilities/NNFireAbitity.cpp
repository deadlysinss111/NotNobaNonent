// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/NNFireAbitity.h"

void UNNFireAbitity::Trigger()
{

    if (!_owner) return;

    UE_LOG(LogTemp, Warning, TEXT("Tourelle tire !"));

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

	GetWorld()->SpawnActor<AActor>(_BPArrow, _owner->GetActorLocation(), direction.ToOrientationRotator());
}