// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#include "Lock.h"
#include "TriggerComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DunegonEscapeCharacter.h"
#include "InventoryComponent.h"
#include "ItemData.h"

ALock::ALock()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	TriggerComponent = CreateDefaultSubobject<UTriggerComponent>(TEXT("TriggerComponent"));
	TriggerComponent->SetupAttachment(SceneRoot);

	KeyItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyItemMesh"));
	KeyItemMesh->SetupAttachment(SceneRoot);
}

void ALock::UpdateLockState(bool bNewIsLocked)
{
	bIsLocked = bNewIsLocked;
	TriggerComponent->Trigger(!bNewIsLocked);
	KeyItemMesh->SetVisibility(!bNewIsLocked);
}

void ALock::Interact(ADunegonEscapeCharacter* Character)
{
	UInventoryComponent* Inventory = Character->GetInventoryComponent();

	if (bIsLocked)
	{
		if (Inventory->RemoveItem(RequiredItem))
		{
			UpdateLockState(false);
		}

		return;
	}

	if (!bAllowMultipleInteractions)
	{
		return;
	}

	UpdateLockState(true);
	Inventory->AddItem(RequiredItem);
}

bool ALock::CanInteract() const
{
	return bIsLocked || bAllowMultipleInteractions;
}