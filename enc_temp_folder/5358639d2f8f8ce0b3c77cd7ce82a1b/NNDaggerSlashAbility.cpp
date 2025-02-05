// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Player/Assassin/NNDaggerSlashAbility.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

void UNNDaggerSlashAbility::Init(APawn* owner) {
	Super::Init(owner);
	
	//TArray<UStaticMeshComponent> StaticComps;
	//_owner->GetComponents** <UStaticMeshComponent>** (StaticComps);

	//for(UStaticMeshComponent** comp : StaticComps)

	FString EmitterName = TEXT("DaggerSlashFX");
	FString AssetPath = FString::Printf(TEXT("NiagaraSystem'/Game/Effects/%s.%s'"), *EmitterName, *EmitterName);
	_slashFX = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, *AssetPath));

	if (!_slashFX)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load Niagara System: %s"), *EmitterName);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("fail to load fx"));
		return;
	}

}


void UNNDaggerSlashAbility::Trigger() {
	//_owner->GetComponentByClass< UNiagaraSystem>();
	_dagger->Slash();

	auto var = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		_owner,
		_slashFX,
		FVector(0, 0, 0),
		FRotator(0, 0, 0),
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