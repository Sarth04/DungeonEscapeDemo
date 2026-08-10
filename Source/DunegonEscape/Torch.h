// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Torch.generated.h"
		
class UPointLightComponent;
class UParticleSystemComponent;
class UStaticMeshComponent;
class APuzzleManager;

UCLASS()
class DUNEGONESCAPE_API ATorch : public AInteractable
{
	GENERATED_BODY()

public:
	ATorch();

	virtual void Interact(ADunegonEscapeCharacter* Character) override;
	virtual int32 GetPuzzleState() const override;

protected:
	virtual void BeginPlay() override;

private:
	void SetLit(bool bNewIsLit);

	UPROPERTY(EditAnywhere, Category = "Torch")
	bool bIsLit = true;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> TorchMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UPointLightComponent> PointLight;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UParticleSystemComponent> FlameVFX;
	
	UPROPERTY(EditInstanceOnly, Category = "Puzzle")
	TObjectPtr<APuzzleManager> PuzzleManager = nullptr;
};