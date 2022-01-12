// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NormalMovementComponent.generated.h"

/**
 * 
 */

UCLASS()
class WHALE_API UNormalMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TestMSG();


	//void MoveTo(FVector Delta, FRotator NewRotation, bool checkCollision);

	//bool TraceForObstacles(UWorld* World, AActor* ActorToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut, EDrawDebugTraceType DrawDebugType = EDrawDebugTraceType::None, bool ReturnPhysMat = false);
	
};
