// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMovementComponent.h"
#include "DrawDebugHelpers.h"

//void UNormalMovementComponent::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	FHitResult OutHit;
//
//	FVector Start = new FVector(0, 0, 0);
//	FVector EndPoint = new FVector(1, 0, 5);
//
//	FCollisionQueryParams CollisionParams;
//
//	//DrawDebugLine(GetWorld(), Start, EndPoint, FColor::Red, false, 1, 0, 1);
//
//	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, EndPoint, ECC_Visibility, CollisionParams);
//
//	if (isHit)
//	{
//		if (OutHit.bBlockingHit)
//		{
//			if (GEngine)
//			{
//				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You hit smtg"));
//			}
//		}
//	}
//
//}

void UNormalMovementComponent::BeginPlay()
{
	UE_LOG(LogTemp, Display, TEXT("Normal movement comp is init"));
	Super::BeginPlay();
}

void UNormalMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}
	//UE_LOG(LogTemp, Display, TEXT("Tick normal comp"));


}

void UNormalMovementComponent::TestMSG()
{
	UE_LOG(LogTemp, Display, TEXT("Test msg"));
}

