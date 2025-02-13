// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Player/Assassin/NNSmokeAbility.h"
#include "Character/NNPlayerCharacter.h"
#include "Perception/AISense_Sight.h"

void UNNSmokeAbility::Init(APawn* owner) {
	Super::Init(owner);
}

void UNNSmokeAbility::Trigger(KeyState state) {
	if (state != KeyState::Start)
		return;

	ANNPlayerCharacter* character = Cast<ANNPlayerCharacter>(_owner);
	UAIPerceptionStimuliSourceComponent* StimuliSource = character->FindComponentByClass<UAIPerceptionStimuliSourceComponent>();
	StimuliSource->UnregisterFromSense(UAISense_Sight::StaticClass());

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, TEXT("Beginning"));
	FTimerHandle UnusedHandle;
	_owner->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UNNSmokeAbility::SetBackVisibility, duration, false);
}


void UNNSmokeAbility::SetBackVisibility() {
	ANNPlayerCharacter* character = Cast<ANNPlayerCharacter>(_owner);
	UAIPerceptionStimuliSourceComponent* StimuliSource = character->FindComponentByClass<UAIPerceptionStimuliSourceComponent>();
	StimuliSource->RegisterForSense(UAISense_Sight::StaticClass());

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, TEXT("End"));
}