// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

class UMover;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNEGONESCAPE_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerComponent();

	void Trigger(bool bTriggered);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UMover> Mover = nullptr;

	UPROPERTY(EditAnywhere, Category = "TriggerComponent")
	TObjectPtr<AActor> MoverActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "TriggerComponent")
	bool bIsTriggered = false;
};