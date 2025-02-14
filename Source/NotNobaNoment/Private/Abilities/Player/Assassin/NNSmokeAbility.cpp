// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Player/Assassin/NNSmokeAbility.h"
#include "Character/NNPlayerCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Sight.h"

void UNNSmokeAbility::Init(APawn* owner) {
	Super::Init(owner);

	FString AssetPath = FString::Printf(TEXT("NiagaraSystem'/Game/Entities/Heroes/Assassin/FX/Smoke.Smoke'"));
	_smokeFX = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), this, *AssetPath));
	if (!_smokeFX)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("fail to load fx"));
		return;
	}
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

	_smokeInstance = UNiagaraFunctionLibrary::SpawnSystemAttached(
		_smokeFX,
		character->GetRootComponent(),
		NAME_None,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::SnapToTarget,
		true
	);
}


void UNNSmokeAbility::SetBackVisibility() {
	ANNPlayerCharacter* character = Cast<ANNPlayerCharacter>(_owner);
	UAIPerceptionStimuliSourceComponent* StimuliSource = character->FindComponentByClass<UAIPerceptionStimuliSourceComponent>();
	StimuliSource->RegisterForSense(UAISense_Sight::StaticClass());

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, TEXT("End"));
}