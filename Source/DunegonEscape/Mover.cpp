// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.


#include "Mover.h"

UMover::UMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMover::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	StartLocation = Owner->GetActorLocation();
	StartRotation = Owner->GetActorRotation();

	TargetLocation = StartLocation + TranslationOffset;
	TargetRotation = StartRotation + RotationOffset;
}

void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((!bIsActivated && CurrentAlpha <= 0.f) || (bIsActivated && CurrentAlpha >= 1.f))
	{
		return;
	}

	UpdateAlpha(DeltaTime);
	UpdateLocation();
	UpdateRotation();
}

void UMover::SetActivated(bool bActivated)
{
	bIsActivated = bActivated;
}

void UMover::UpdateAlpha(float DeltaTime)
{
	if (bIsActivated)
	{
		CurrentAlpha += DeltaTime / MovementDuration;
	}
	else
	{
		CurrentAlpha -= DeltaTime / MovementDuration;
	}

	CurrentAlpha = FMath::Clamp(CurrentAlpha, 0.f, 1.f);
}

void UMover::UpdateLocation()
{
	FVector NewLocation = FMath::Lerp(StartLocation, TargetLocation, CurrentAlpha);
	Owner->SetActorLocation(NewLocation);
}

void UMover::UpdateRotation()
{
	FRotator NewRotation = FMath::Lerp(StartRotation, TargetRotation, CurrentAlpha);
	Owner->SetActorRotation(NewRotation);
}