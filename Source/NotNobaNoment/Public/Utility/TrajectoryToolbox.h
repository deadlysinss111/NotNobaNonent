// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class NOTNOBANOMENT_API TrajectoryToolbox
{
public:
	TrajectoryToolbox();
	~TrajectoryToolbox();

public:
	static FVector BellCurveInitialVelocity(FVector startPoint, FVector endPoint, float apex, float gravity);
	static TArray<FVector> LineRenderWithDirection(FVector origin, FVector direction, AActor* actorToIgnore, int splineSize, float step = 1);
};
