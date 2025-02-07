// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Player/Assassin/NNThrowDaggerAbility.h"

void UNNThrowDaggerAbility::Init(APawn* owner) {
	Super::Init(owner);

	_currentAction.BindUFunction(this, FName("Throw"));

	TArray<AActor*> AttachedActors;
	_owner->GetAttachedActors(AttachedActors);
	for (AActor* Child : AttachedActors)
	{
		ANNDagger* dagger = Cast<ANNDagger>(Child);
		if (dagger)
		{
			_dagger = dagger;
		}
	}
}

void UNNThrowDaggerAbility::Trigger() {
	_currentAction.Execute();
}

void UNNThrowDaggerAbility::Throw() {
	_dagger->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	if (UPrimitiveComponent* PhysComp = Cast<UPrimitiveComponent>(_dagger->GetRootComponent()))
	{
		
		PhysComp->SetSimulatePhysics(true);
		FVector ForwardDirection = _owner->GetActorForwardVector();
		FVector Force = ForwardDirection * 100000;
		PhysComp->AddImpulse(Force);
	}

	_dagger->ChangeState(ANNDagger::DaggerState::Flying);
	_currentAction.BindUFunction(this, FName("Jump"));
}

void UNNThrowDaggerAbility::Jump() {

	_dagger->ChangeState(ANNDagger::DaggerState::Handed);
	_currentAction.BindUFunction(this, FName("Throw"));
}