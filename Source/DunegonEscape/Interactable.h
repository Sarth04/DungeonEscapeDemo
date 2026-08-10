// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

class UMaterialInterface;
class UStaticMeshComponent;
class ADunegonEscapeCharacter;

UCLASS()
class DUNEGONESCAPE_API AInteractable : public AActor
{
	GENERATED_BODY()

public:
	AInteractable();

	void OnFocusBegin();
	void OnFocusEnd();
	virtual void Interact(ADunegonEscapeCharacter* Character);
	virtual bool CanInteract() const;
	virtual int32 GetPuzzleState() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	UMaterialInterface* OutlineMaterial;

private:
	void SetOutlineMaterial(UMaterialInterface* Material);
};