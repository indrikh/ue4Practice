// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "DrawDebugHelpers.h"
#include "NormalMovementComponent.h"


// Sets default values
AMyCharacter::AMyCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UNormalMovementComponent>(AMyCharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Display, TEXT("The boolean value is %s"), (NormalMovement != NULL ? TEXT("true") : TEXT("false")));
	//NormalMovement = Cast<UNormalMovementComponent>(Super::GetMovementComponent());
	//NormalMovement->TestMSG();
	UE_LOG(LogTemp, Display, TEXT("Super comp is %s"), (Super::GetMovementComponent() != NULL ? TEXT("true") : TEXT("false")));
	/*NormalMovement = CreateDefaultSubobject<UNormalMovementComponent>(TEXT("NormalMovementComponent"));
	NormalMovement->UpdatedComponent = RootComponent;*/
	UE_LOG(LogTemp, Display, TEXT("The boolean value is %s"), (NormalMovement != NULL ? TEXT("true") : TEXT("false")));

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

	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::CameraPitch);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::CameraYaw);

}

void AMyCharacter::MoveForward(float axisValue)
{
	// AMyCharacter::GetMovementComponent()->AddInputVector(GetActorForwardVector() * axisValue);

	if (NormalMovement && (NormalMovement->UpdatedComponent == RootComponent))
	{
		UE_LOG(LogTemp, Display, TEXT("Vector value is %s"), *(GetActorForwardVector() * axisValue).ToString());
		NormalMovement->AddInputVector(GetActorForwardVector() * axisValue);
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::SanitizeFloat(axisValue));
	}

	if (NormalMovement == NULL)
	{
		//UE_LOG(LogTemp, Display, TEXT("NULL FCK NULL"));

	}
}

void AMyCharacter::CameraPitch(float AxisValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, TEXT("Pitch"));
}

void AMyCharacter::CameraYaw(float AxisValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, TEXT("Yaw"));
}