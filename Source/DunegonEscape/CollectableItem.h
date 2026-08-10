// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "CollectableItem.generated.h"

class ADunegonEscapeCharacter;
class UItemData;

UCLASS()
class DUNEGONESCAPE_API ACollectableItem : public AInteractable
{
	GENERATED_BODY()

public:
	ACollectableItem();

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TObjectPtr<UItemData> ItemData;

	virtual void Interact(ADunegonEscapeCharacter* Character) override;
};