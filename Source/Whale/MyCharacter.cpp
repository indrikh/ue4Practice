// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "DrawDebugHelpers.h"
#include "NormalMovementComponent.h"


// Sets default values
AMyCharacter::AMyCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UNormalMovementComponent>(AMyCharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;


	FPCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FPSpringArm"));
	FPCameraSpringArm->SetupAttachment(RootComponent);
	FPCameraSpringArm->TargetArmLength = 300.0f;
	FPCameraSpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	Camera->SetupAttachment(FPCameraSpringArm, USpringArmComponent::SocketName);

	Camera->bUsePawnControlRotation = false;

	TraceLength = 150;

}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	NormalMovement = Cast<UNormalMovementComponent>(Super::GetMovementComponent());
}

//UNormalMovementComponent* AMyCharacter::GetMovementComponent() const
//{
//	return NormalMovement;
//}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AMyCharacter::TraceForGround();

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::SanitizeFloat());

	/*FHitResult OutHit;

	FVector Start = FVector(0, 0, 0);
	FVector EndPoint = FVector(1, 0, 5);

	FCollisionQueryParams CollisionParams;

	DrawDebugLine(GetWorld(), Start, EndPoint * 5, FColor::Red, false, 1, 0, 1);

	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, EndPoint, ECC_Visibility, CollisionParams);

	if (isHit)
	{
		if (OutHit.bBlockingHit)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Simple message"));
			}
		}
	}*/

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::CameraPitch);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::CameraYaw);

}

void AMyCharacter::MoveForward(float axisValue)
{
	if (NormalMovement && (NormalMovement->UpdatedComponent == RootComponent))
	{
		NormalMovement->AddInputVector(GetActorForwardVector() * axisValue);
	}
}

void AMyCharacter::MoveRight(float axisValue)
{
	if (NormalMovement && (NormalMovement->UpdatedComponent == RootComponent))
	{
		NormalMovement->AddInputVector(GetActorRightVector() * axisValue);
	}
}

void AMyCharacter::TraceForGround()
{

	FHitResult HitOut;

	FVector Start = GetActorLocation();
	FVector End = FVector(Start.X, Start.Y, Start.Z - TraceLength);

	FCollisionQueryParams TraceParams;

	GetWorld()->LineTraceSingleByChannel(HitOut, Start, End, ECC_Visibility, TraceParams);

	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1, 0, 1);

	if (HitOut.bBlockingHit)
	{
		DrawDebugPoint(GetWorld(), HitOut.Location, 20.f, FColor::Red, false, 1.f, SDPG_World);
		DrawDebugLine(GetWorld(), HitOut.Location, Start, FColor::Green, false, 1.f, SDPG_World, 2.f);
		HitTraceNormal = HitOut.Normal;
		//DrawDebugDirectionalArrow(GetWorld(), HitTraceNormal, HitTraceNormal)
		SetActorRotation(HitTraceNormal.Rotation());
	}
}

void AMyCharacter::CameraPitch(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AMyCharacter::CameraYaw(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}