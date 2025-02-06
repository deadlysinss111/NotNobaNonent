// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Player/Assassin/NNDaggerSlashAbility.h"
#include "NiagaraFunctionLibrary.h"
//#include "AnimInstance.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

void UNNDaggerSlashAbility::Init(APawn* owner) {
	Super::Init(owner);
	
	//TArray<UStaticMeshComponent> StaticComps;
	//_owner->GetComponents** <UStaticMeshComponent>** (StaticComps);

	//for(UStaticMeshComponent** comp : StaticComps)

	FString AssetPath = FString::Printf(TEXT("NiagaraSystem'/Game/Entities/Heroes/Assassin/Abilities/DaggerSlash/DaggerSlashFX.DaggerSlashFX'"));
	_slashFX = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), this, *AssetPath));

	if (!_slashFX)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("fail to load fx"));
		return;
	}

}


void UNNDaggerSlashAbility::Trigger() {
	//_owner->GetComponentByClass< UNiagaraSystem>();
	//_dagger->Slash();

	_owner->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance()->RequestTransitionEvent(TEXT("Attack"), .1f, (ETransitionRequestQueueMode)0, (ETransitionRequestOverwriteMode)0);

	auto var = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		_owner,
		_slashFX,
		_owner->GetActorLocation(),
		_owner->GetActorRotation(),
		FVector(1.0f), // Scale
		true,          // Auto Destroy
		true,          // Auto Activate
		ENCPoolMethod::None,
		true           // Preload assets
	);

	if(var!= NULL)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("null"));

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("child"));
}