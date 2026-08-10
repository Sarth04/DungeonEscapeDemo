// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#include "PuzzleManager.h"
#include "TriggerComponent.h"
#include "Interactable.h"

APuzzleManager::APuzzleManager()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	TriggerComponent = CreateDefaultSubobject<UTriggerComponent>(TEXT("TriggerComponent"));
	TriggerComponent->SetupAttachment(SceneRoot);
}

void APuzzleManager::BeginPlay()
{
	Super::BeginPlay();

    CheckPuzzle();
}

void APuzzleManager::CheckPuzzle()
{
    if (PuzzleElements.Num() != RequiredStates.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: Puzzle elements count doesn't match RequiredStates count."),*GetName());

        return;
    }

    bool bSolved = true;

    for (int32 Index = 0; Index < PuzzleElements.Num(); ++Index)
    {
        if (!PuzzleElements[Index])
        {
            UE_LOG(LogTemp, Warning,TEXT("%s: Puzzle element %d is nullptr."), *GetName(), Index);

            return;
        }

        if (PuzzleElements[Index]->GetPuzzleState() != RequiredStates[Index])
        {
            bSolved = false;
            break;
        }
    }

    TriggerComponent->Trigger(bSolved);
}