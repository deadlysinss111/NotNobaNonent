// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Player/Assassin/NNThrowDaggerAbility.h"
#include "Utility/TrajectoryToolbox.h"

void UNNThrowDaggerAbility::Init(APawn* owner) {
	Super::Init(owner);

	_currentAction.BindUFunction(this, FName("RenderCurve"));

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

    FString AssetPath = FString::Printf(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
    _mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), this, *AssetPath));

    AssetPath = FString::Printf(TEXT("Material'/Game/StarterContent/Materials/M_AssetPlatform.M_AssetPlatform'"));
    _material = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), this, *AssetPath));


    /*_spline = NewObject<USplineComponent>(_owner);
    _spline->RegisterComponent();
    _spline->AttachToComponent(_owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

    _splineMeshes.Reserve(500);*/
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

void UNNThrowDaggerAbility::ResetCurve() {
    _splineMeshes.Reset(500);
    _spline->ClearSplinePoints();
}

void UNNThrowDaggerAbility::RenderCurve() {
    /*ResetCurve();

    FVector direction;
    {
        FHitResult HitResult;
        FVector start = _owner->GetActorLocation();
        FVector ForwardVector = _owner->GetActorForwardVector();
        FVector end = start + (ForwardVector * 10.0f);

        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(_owner);

        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, start, end, ECC_Visibility, QueryParams);

        direction = TrajectoryToolbox::BellCurveInitialVelocity(start, end, 1, 1000);
    }

    TArray<FVector> points = TrajectoryToolbox::LineRenderWithDirection(_owner->GetNavAgentLocation(), direction, _owner);

    for (const FVector& point : points) {
        _spline->AddSplinePoint(point, ESplineCoordinateSpace::World);
    }

    

    int NumPoints = _spline->GetNumberOfSplinePoints();
    for (int i = 0; i < NumPoints - 1; i++) {
        USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(_owner);
        SplineMesh->RegisterComponent();
        SplineMesh->AttachToComponent(_spline, FAttachmentTransformRules::KeepRelativeTransform);
        SplineMesh->SetMobility(EComponentMobility::Movable);
        SplineMesh->SetStaticMesh(_mesh);
        if (_material) {
            SplineMesh->SetMaterial(0, _material);
        }

        FVector StartPos = _spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        FVector StartTangent = _spline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::World);
        FVector EndPos = _spline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World);
        FVector EndTangent = _spline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::World);

        SplineMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);
    }*/
}