// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Player/Assassin/NNDagger.h"

// Sets default values
ANNDagger::ANNDagger()
{
	PrimaryActorTick.bCanEverTick = true;

	/*InitSmth<ANNDagger>(this);
	_currentStateAction = std::bind_front(&ANNDagger::HandedOverlapAction, this);*/

}

void ANNDagger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANNDagger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANNDagger::OnActorEnter(AActor* OtherActor)
{
	// Could someone tell me why that line makes crash??
	//_currentStateAction(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("overlap"));
}

void ANNDagger::ChangeState(DaggerState newState)
{
	_currentState = newState;
	switch (newState) {
		case DaggerState::Handed:
			_currentStateAction = std::bind_front(&ANNDagger::HandedOverlapAction, this);
			break;
		case DaggerState::Hitting:
			_currentStateAction = std::bind_front(&ANNDagger::HittingOverlapAction, this);
			break;
		case DaggerState::Flying:
			_currentStateAction = std::bind_front(&ANNDagger::FlyingOverlapAction, this);
			break;
		case DaggerState::Grounded:
			_currentStateAction = std::bind_front(&ANNDagger::GroundedOverlapAction, this);
			break;
	}
}

void ANNDagger::HandedOverlapAction(AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("HANDED"));
}

void ANNDagger::HittingOverlapAction(AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("HITTING"));
}

void ANNDagger::FlyingOverlapAction(AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("FLYING"));
}

void ANNDagger::GroundedOverlapAction(AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("GROUNDED"));
}

void ANNDagger::Slash()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SLASH"));
}

void ANNDagger::Throw()
{

}