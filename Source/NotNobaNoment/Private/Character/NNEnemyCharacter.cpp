// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NNEnemyCharacter.h"
#include "Character/NNPlayerCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void ANNEnemyCharacter::BeginPlay() {
	Super::BeginPlay();

	_blackBoard = UAIBlueprintHelperLibrary::GetBlackboard(this);

	for (TSubclassOf<UNNEnemyAbility> abilityData : _abilitySet->_abilities) {
		UNNEnemyAbility* ability = NewObject<UNNEnemyAbility>(this, abilityData);
		ability->Init(this);
		_abilities.Add(ability);
	}
}

void ANNEnemyCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (_isBeingKnockbacked) {
		SetActorLocation(GetActorLocation() + _KBDisplacementPerFrame);
		float dist = (GetActorLocation() - _KBTargetPos).Length();
		if (dist <= .1f || dist >= _KBLastDist) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("AGARIO"));
			_isBeingKnockbacked = false;
		}
		else
			_KBLastDist = dist;
		
	}
}

void ANNEnemyCharacter::KnockBack(AActor* OtherActor) {
	FVector dir = GetActorLocation() - OtherActor->GetActorLocation();
	dir.Z = 0;
	dir.Normalize();
	_KBTargetPos = GetActorLocation() + dir * 250;
	_KBDisplacementPerFrame = FMath::Lerp(0, dir * 250, .2f);
	_isBeingKnockbacked = true;
	_KBLastDist = 100000;
}


void ANNEnemyCharacter::OnActorEnter(AActor* OtherActor) {

	if (false == _provideContactDamage)
		return;

	if (ANNPlayerCharacter* player = Cast<ANNPlayerCharacter>(OtherActor)) {
		player->GetHealthComponent()->ApplyDamage(20);
	}
}