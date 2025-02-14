// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Player/Assassin/NNDagger.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/NNPlayerCharacter.h"
#include "Character/NNEnemyCharacter.h"

// Sets default values
ANNDagger::ANNDagger()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerComponent = CreateDefaultSubobject<UNNCollisionComponent>(TEXT("TriggerComponent"));

	InitEventComponent<ANNDagger>(this);

	_currentStateAction.BindUFunction(this, FName("HandedOverlapAction"));
}

void ANNDagger::BeginPlay()
{
	Super::BeginPlay();
	
	FString AssetPath = FString::Printf(TEXT("NiagaraSystem'/Game/Entities/Heroes/Assassin/Abilities/DaggerSlash/DaggerSlashFX.DaggerSlashFX'"));
	_pickupAttackFX = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), this, *AssetPath));

	if (!_pickupAttackFX)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("fail to load fx"));
		return;
	}
}

void ANNDagger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANNDagger::OnActorEnter(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("overlap"));
	if (_currentStateAction.IsBound()) {
		_currentStateAction.Execute(OtherActor);
	}
}

void ANNDagger::OnActorHit(AActor* OtherActor, const FHitResult& Hit)
{
	/*if (_currentStateAction.IsBound()) {
		_currentStateAction.Execute(OtherActor);
	}*/
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit"));
}

void ANNDagger::ChangeState(DaggerState newState)
{
	_currentState = newState;
	switch (newState) {
		case DaggerState::Handed:
			_currentStateAction.BindUFunction(this, FName("HandedOverlapAction"));
			break;
		case DaggerState::Hitting:
			_currentStateAction.BindUFunction(this, FName("HittingOverlapAction"));
			break;
		case DaggerState::Flying:
			_currentStateAction.BindUFunction(this, FName("FlyingOverlapAction"));
			break;
		case DaggerState::Grounded:
			_currentStateAction.BindUFunction(this, FName("GroundedOverlapAction"));
			break;
	}
}

void ANNDagger::HandedOverlapAction(AActor* OtherActor) {
}

void ANNDagger::HittingOverlapAction(AActor* OtherActor) {

	if (OtherActor->Implements<UNNEntityInterface>())
	{
		//LOG entity name
		UE_LOG(LogTemp, Warning, TEXT("HITTING %s"), *OtherActor->GetName());
		if (ANNPlayerCharacter* entity = Cast<ANNPlayerCharacter>(OtherActor))
			return;
		
		//LOG
		UE_LOG(LogTemp, Warning, TEXT("HITTING %s"), *OtherActor->GetName());

		INNEntityInterface* entity = Cast<INNEntityInterface>(OtherActor);
		if (entity && entity->GetHealthComponent() != nullptr)
		{
			//LOG entity name
			UE_LOG(LogTemp, Warning, TEXT("HITTING %s"), *OtherActor->GetName());


			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("DAMMAGE by Dagger 10"));
			entity->GetHealthComponent()->ApplyDamage(_dammage);

			if (ANNEnemyCharacter* enemy = Cast<ANNEnemyCharacter>(OtherActor)) {
				enemy->KnockBack(this);
			}
		}
	}

	//TODE: Add nockback function
}

void ANNDagger::FlyingOverlapAction(AActor* OtherActor) {
	if (OtherActor->ActorHasTag("Wall")) {
		if (UPrimitiveComponent* PhysComp = Cast<UPrimitiveComponent>(GetRootComponent()))
		{
			PhysComp->SetSimulatePhysics(false);
			//PhysComp->SetEnableGravity(false);
			PhysComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
			PhysComp->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("touched ground"));
			//ChangeState(DaggerState::Grounded);
			SetActorRotation(FRotator::MakeFromEuler(FVector(150, 0, 0)));
			_ObjectsHitOnTheFly.Empty();
		}
	}
	else if (ANNPlayerCharacter* character = Cast<ANNPlayerCharacter>(OtherActor)) {
		/*GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("touched player"));*/
		if (UPrimitiveComponent* PhysComp = Cast<UPrimitiveComponent>(GetRootComponent()))
		{
			PhysComp->SetSimulatePhysics(false);
			//PhysComp->SetEnableGravity(false);
			PhysComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
			PhysComp->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
			ChangeState(DaggerState::Handed);
			PickupAttack(character);
			_ObjectsHitOnTheFly.Empty();
		}
	}
	else if(INNEntityInterface* entity = Cast<INNEntityInterface>(OtherActor)){
		if (_ObjectsHitOnTheFly.Contains(OtherActor))
			return;

		entity->GetHealthComponent()->ApplyDamage(_dammage);
		_ObjectsHitOnTheFly.Add(OtherActor);

		if (ANNEnemyCharacter* enemy = Cast<ANNEnemyCharacter>(OtherActor)) {
				
			enemy->KnockBack(this);
		}
	}
}

void ANNDagger::GroundedOverlapAction(AActor* OtherActor) {

	//Change une condition de collision pour pouvoir ramasser le couteau

	UPrimitiveComponent* PhysComp = Cast<UPrimitiveComponent>(GetRootComponent());
	//LOG PhysComp->GetName()
	if (PhysComp)
	{
		//LOG PhysComp->GetName()
		UE_LOG(LogTemp, Warning, TEXT("PhysComp->GetName() %s"), *PhysComp->GetName());
	}

	if (ANNPlayerCharacter* character = Cast<ANNPlayerCharacter>(OtherActor)) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("GROUNDED"));
		PickupAttack(character);
	}
}

void ANNDagger::PickupAttack(ANNPlayerCharacter* OtherActor) {
	AttachToComponent(OtherActor->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_RSocket"));

	auto var = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		OtherActor,
		_pickupAttackFX,
		GetActorLocation() + FVector(0, 0, 1),
		OtherActor->GetActorRotation(),
		FVector(1.0f), // Scale
		true,          // Auto Destroy
		true,          // Auto Activate
		ENCPoolMethod::None,
		true           // Preload assets
	);


	TArray<AActor*> outActors;
	FVector sphereCenter = GetActorLocation();
	float sphereRadius = 500.0f;

	bool bOverlap = UKismetSystemLibrary::SphereOverlapActors(
		OtherActor,                // World context
		sphereCenter,              // Sphere center
		sphereRadius,              // Radius
		{ UEngineTypes::ConvertToObjectType(ECC_Pawn) }, // Object types to detect (only Pawns in this case)
		AActor::StaticClass(),     // Only detect Actors of this class (nullptr = any)
		TArray<AActor*>(),         // Ignore these actors
		outActors                  // Output array of actors
	);

	for (AActor* target : outActors) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("hit smth"));
	}
}


void ANNDagger::Slash()
{
	ChangeState(DaggerState::Hitting);
	// The state is set back to Handed trough the animation
}

void ANNDagger::SetBackToHanded() {
	ChangeState(DaggerState::Handed);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("backtohanded"));
}