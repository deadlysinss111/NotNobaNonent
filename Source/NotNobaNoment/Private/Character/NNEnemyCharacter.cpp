// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NNEnemyCharacter.h"

void ANNEnemyCharacter::KnockBack(AActor* OtherActor) {
	FVector dir = GetActorLocation() - OtherActor->GetActorLocation();
	dir.Normalize();
	SetActorLocation(GetActorLocation() + dir * 100); // TODO: change values, those are just for testing
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("hitted enemy"));
}