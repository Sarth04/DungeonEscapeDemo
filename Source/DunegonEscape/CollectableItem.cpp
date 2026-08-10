// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#include "CollectableItem.h"
#include "DunegonEscapeCharacter.h"
#include "InventoryComponent.h"

ACollectableItem::ACollectableItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACollectableItem::Interact(ADunegonEscapeCharacter* Character)
{
    if (!ItemData)
    {
        UE_LOG(LogTemp, Error, TEXT("%s has no ItemData assigned!"), *GetName());
        return;
    }

    Character->GetInventoryComponent()->AddItem(ItemData);
    Destroy();
}