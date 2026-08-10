// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Lock.generated.h"

class UTriggerComponent;
class UStaticMeshComponent;
class ADunegonEscapeCharacter;
class UItemData;

UCLASS()
class DUNEGONESCAPE_API ALock : public AInteractable
{
	GENERATED_BODY()

public:	
	ALock();

	virtual void Interact(ADunegonEscapeCharacter* Character) override;
	virtual bool CanInteract() const override;
	
private:
	void UpdateLockState(bool bNewIsKeyPlaced);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UTriggerComponent* TriggerComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* KeyItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	TObjectPtr<UItemData> RequiredItem;

	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	bool bIsLocked = true;

	UPROPERTY(EditDefaultsOnly, Category = "Lock")
	bool bAllowMultipleInteractions = false;
};