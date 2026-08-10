// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "RotatableStatue.generated.h"

class UStaticMeshComponent;
class APuzzleManager;

UCLASS()
class DUNEGONESCAPE_API ARotatableStatue : public AInteractable
{
    GENERATED_BODY()

public:
    ARotatableStatue();

    virtual void Interact(ADunegonEscapeCharacter* Character) override;
    virtual int32 GetPuzzleState() const override;
    virtual bool CanInteract() const override;

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;
        
private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<USceneComponent> SceneRoot;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UStaticMeshComponent> BaseMesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UStaticMeshComponent> RotatingMesh;

    UPROPERTY(EditAnywhere, Category = "Puzzle")
    int32 CurrentRotationState = 0;

    UPROPERTY(EditInstanceOnly, Category = "Puzzle")
    TObjectPtr<APuzzleManager> PuzzleManager = nullptr;

    UPROPERTY(EditAnywhere, Category = "Puzzle", meta = (ClampMin = "2"))
    int32 RotationStates = 4;

    UPROPERTY(EditAnywhere, Category = "Rotation")
    float RotationSpeed = 180.f;

    float CurrentYaw = 0.f;
    float TargetYaw = 0.f;
    float RotationStep = 90.f;
    bool bIsRotating = false;
};