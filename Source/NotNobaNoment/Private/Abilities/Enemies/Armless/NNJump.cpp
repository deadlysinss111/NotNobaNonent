// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Enemies/Armless/NNJump.h"
#include "Character/NNEnemyCharacter.h"
#include "Character/NNPlayerCharacter.h"


void UNNJump::Init(APawn* owner) {
	Super::Init(owner);
}


void UNNJump::Trigger() {
	// Animate spring
	/*FTimerHandle UnusedHandle;
	_owner->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UNNJump::OnDelayOver, 2, false);*/

	
}

void UNNJump::OnDelayOver() 
{

	ANNEnemyCharacter* armless = Cast<ANNEnemyCharacter>(_owner);
	//armless->GetCollisionComponent()->OnActorEnter.AddDynamic(this, &ThisClass::OnActorEnter);
	AActor* target = Cast<AActor>(armless->_blackBoard->GetValueAsClass(TEXT("TargetActor")));
	if(target != NULL)
		_owner->SetActorLocation(target->GetActorLocation());
}


void UNNJump::OnActorEnter(AActor* OtherActor)
{
	if(OtherActor->ActorHasTag("Wall")) {
		//ANNEnemyCharacter* armless = Cast<ANNEnemyCharacter>(_owner);
		//armless->GetCollisionComponent()->OnActorEnter.RemoveDynamic(this, &ThisClass::OnActorEnter);
		_ObjectsHitOnTheFly.Empty();
	}
	else if (ANNPlayerCharacter* character = Cast<ANNPlayerCharacter>(OtherActor)) {
		if (_ObjectsHitOnTheFly.Contains(OtherActor))
			return;

		character->GetHealthComponent()->ApplyDamage(15);
		_ObjectsHitOnTheFly.Add(OtherActor);
	}
}