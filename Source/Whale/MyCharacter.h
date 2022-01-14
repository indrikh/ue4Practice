// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "MyCharacter.generated.h"





UCLASS()
class WHALE_API AMyCharacter : public ACharacter
{

	GENERATED_BODY()

public:

	UPROPERTY(Category = "Character", VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;

	UPROPERTY(Category = "Character", VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* FPCameraSpringArm;

	UPROPERTY(Category = "Character", VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* CharacterBodyMesh;


	// Sets default values for this character's properties
	AMyCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	//virtual UNormalMovementComponent* GetMovementComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Pawn|Character")
	void MoveForward(float axisValue);

	void MoveRight(float axisValue);

	void CameraPitch(float AxisValue);

	void CameraYaw(float AxisValue);

	void TraceForGround();

	UPROPERTY(Category = "Trace", BlueprintReadWrite, EditAnywhere)
	float TraceLength;

private: 

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UNormalMovementComponent* NormalMovement;

	FVector HitTraceNormal;

};
