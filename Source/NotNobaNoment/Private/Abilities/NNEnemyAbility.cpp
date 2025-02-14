// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/NNEnemyAbility.h"
#include "Character/NNEnemyCharacter.h"

void UNNEnemyAbility::Init(APawn* owner) {
	_owner = owner;
}