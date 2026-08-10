// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemData;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNEGONESCAPE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	void AddItem(UItemData* Item);

	bool RemoveItem(UItemData* Item);

	bool HasItem(UItemData* Item) const;

private:
	bool ValidateItem(UItemData* Item) const;

	UPROPERTY()
	TArray<TObjectPtr<UItemData>> Items;
};