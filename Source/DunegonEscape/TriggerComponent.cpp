// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.


#include "TriggerComponent.h"
#include "Mover.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!MoverActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: MoverActor is not assigned."), *GetName());
		return;
	}

	Mover = MoverActor->FindComponentByClass<UMover>();

	if (!Mover)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Mover component not found on %s."),*GetName(),*MoverActor->GetName());
	}
}

void UTriggerComponent::Trigger(bool bTriggered)
{
	bIsTriggered = bTriggered;

	if (Mover)
	{
		Mover->SetActivated(bIsTriggered);
	}
}