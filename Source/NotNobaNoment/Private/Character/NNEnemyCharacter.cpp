// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NNEnemyCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void ANNEnemyCharacter::BeginPlay() {
	_blackBoard = UAIBlueprintHelperLibrary::GetBlackboard(this);
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