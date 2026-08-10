// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleManager.generated.h"

class AInteractable;
class UTriggerComponent;

UCLASS()
class DUNEGONESCAPE_API APuzzleManager : public AActor
{
	GENERATED_BODY()

public:
	APuzzleManager();

	void CheckPuzzle();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditInstanceOnly, Category = "Puzzle")
	TArray<TObjectPtr<AInteractable>> PuzzleElements;

	UPROPERTY(EditInstanceOnly, Category = "Puzzle")
	TArray<int32> RequiredStates;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UTriggerComponent> TriggerComponent;
};