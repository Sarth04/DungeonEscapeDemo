// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.


#include "InventoryComponent.h"
#include "ItemData.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInventoryComponent::ValidateItem(UItemData* Item) const
{
	if (Item)
	{
		return true;
	}

	UE_LOG(LogTemp, Error, TEXT("InventoryComponent: Item is nullptr."));
	return false;
}

void UInventoryComponent::AddItem(UItemData* Item)
{
	if (!ValidateItem(Item))
	{
		return;
	}

	Items.Add(Item);
}

bool UInventoryComponent::RemoveItem(UItemData* Item)
{
	if (!ValidateItem(Item))
	{
		return false;
	}

	return Items.RemoveSingle(Item) > 0;
}

bool UInventoryComponent::HasItem(UItemData* Item) const
{
	if (!ValidateItem(Item))
	{
		return false;
	}

	return Items.Contains(Item);
}