// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.


#include "RotatableStatue.h"
#include "Components/StaticMeshComponent.h"
#include "PuzzleManager.h"

ARotatableStatue::ARotatableStatue()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    BaseMesh->SetupAttachment(SceneRoot);

    RotatingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RotatingMesh"));
    RotatingMesh->SetupAttachment(BaseMesh);
}

void ARotatableStatue::BeginPlay()
{
    Super::BeginPlay();

    RotationStep = 360.f / RotationStates;

    CurrentYaw = CurrentRotationState * RotationStep;
    TargetYaw = CurrentYaw;

    RotatingMesh->SetRelativeRotation(FRotator(0.f, CurrentYaw, 0.f));
}

void ARotatableStatue::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsRotating)
    {
        CurrentYaw = FMath::FixedTurn(CurrentYaw, TargetYaw, RotationSpeed * DeltaTime);

        if (FMath::IsNearlyEqual(CurrentYaw, TargetYaw, 0.1f))
        {
            CurrentYaw = TargetYaw;
            bIsRotating = false;
        }

        RotatingMesh->SetRelativeRotation(FRotator(0.f, CurrentYaw, 0.f));
    }
}

void ARotatableStatue::Interact(ADunegonEscapeCharacter* Character)
{
    UE_LOG(LogTemp, Warning, TEXT("Interact: TargetYaw=%f CurrentYaw=%f"), TargetYaw, CurrentYaw);

    bIsRotating = true;

    CurrentRotationState = (CurrentRotationState + 1) % RotationStates;
    TargetYaw = CurrentRotationState * RotationStep;

    if (PuzzleManager)
    {
        PuzzleManager->CheckPuzzle();
    }
}

int32 ARotatableStatue::GetPuzzleState() const
{
    return CurrentRotationState;
}

bool ARotatableStatue::CanInteract() const
{
    return !bIsRotating;
}