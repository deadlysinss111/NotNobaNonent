// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Player/Assassin/NNDaggerSlashAbility.h"

void UNNDaggerSlashAbility::Init(APawn* owner) {
	Super::Init(owner);
	
	//TArray<UStaticMeshComponent> StaticComps;
	//_owner->GetComponents** <UStaticMeshComponent>** (StaticComps);

	//for(UStaticMeshComponent** comp : StaticComps)

}


void UNNDaggerSlashAbility::Trigger() {
	_dagger->Slash();
}