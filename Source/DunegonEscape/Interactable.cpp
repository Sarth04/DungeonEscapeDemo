// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#include "Interactable.h"
#include "Components/StaticMeshComponent.h"

AInteractable::AInteractable()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInteractable::SetOutlineMaterial(UMaterialInterface* Material)
{
	TArray<UStaticMeshComponent*> Meshes;
	GetComponents<UStaticMeshComponent>(Meshes);

	for (UStaticMeshComponent* Mesh : Meshes)
	{
		Mesh->SetOverlayMaterial(Material);
	}
}

void AInteractable::OnFocusBegin()
{
	if (!OutlineMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: OutlineMaterial is nullptr"), *GetName());
		return;
	}

	SetOutlineMaterial(OutlineMaterial);
}

void AInteractable::OnFocusEnd()
{
	SetOutlineMaterial(nullptr);
}

void AInteractable::Interact(ADunegonEscapeCharacter* Character)
{
	checkNoEntry();
}

bool AInteractable::CanInteract() const
{
	return true;
}

int32 AInteractable::GetPuzzleState() const
{
	checkNoEntry();
	return 0;
}