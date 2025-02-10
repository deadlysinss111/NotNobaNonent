// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Player/Assassin/NNThrowDaggerAbility.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
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

void UNNThrowDaggerAbility::RenderCurve() {
    // Create and register the spline component
    USplineComponent* Spline = NewObject<USplineComponent>(_owner);
    Spline->RegisterComponent();
    Spline->AttachToComponent(_owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    Spline->ClearSplinePoints(); // Clear old points

    FVector direction;

    {
        // Raycast
        FHitResult HitResult;
        FVector start = _owner->GetActorLocation();
        FVector ForwardVector = _owner->GetActorForwardVector();
        FVector end = start + (ForwardVector * 10.0f);

        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(_owner);

        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, start, end, ECC_Visibility, QueryParams);

        direction = TrajectoryToolbox::BellCurveInitialVelocity(start, end, 1, 1000);
    }

    // Generate trajectory points
    TArray<FVector> points = TrajectoryToolbox::LineRenderWithDirection(_owner->GetNavAgentLocation(), direction, _owner);

    // Add points to the spline
    for (const FVector& point : points) {
        Spline->AddSplinePoint(point, ESplineCoordinateSpace::World);
    }

    /*FString AssetPath = FString::Printf(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube'"));
    _mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), this, *AssetPath));

    AssetPath = FString::Printf(TEXT("Material'/Game/StarterContent/Materials/M_AssetPlatform'"));
    _material = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), this, *AssetPath));

    GenerateSplineMesh(Spline, _mesh, _material);*/
}

void UNNThrowDaggerAbility::GenerateSplineMesh(USplineComponent* Spline, UStaticMesh* Mesh, UMaterialInterface* Material) {
    //if (!Spline || !Mesh) return;

    //int NumPoints = Spline->GetNumberOfSplinePoints();
    //for (int i = 0; i < NumPoints - 1; i++) {
    //    USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(_owner);
    //    SplineMesh->RegisterComponent();
    //    SplineMesh->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);
    //    SplineMesh->SetMobility(EComponentMobility::Movable);
    //    SplineMesh->SetStaticMesh(Mesh);
    //    if (Material) {
    //        SplineMesh->SetMaterial(0, Material);
    //    }

    //    // Set start and end positions with tangents
    //    FVector StartPos = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
    //    FVector StartTangent = Spline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::World);
    //    FVector EndPos = Spline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World);
    //    FVector EndTangent = Spline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::World);

    //    SplineMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);
    //}
}