// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#include "Torch.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PuzzleManager.h"

ATorch::ATorch()
{
	TorchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorchMesh"));
	SetRootComponent(TorchMesh);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(TorchMesh);

	FlameVFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FlameVFX"));
	FlameVFX->SetupAttachment(TorchMesh);
}

void ATorch::BeginPlay()
{
	Super::BeginPlay();
	SetLit(bIsLit);
}

void ATorch::SetLit(bool bNewIsLit)
{
	bIsLit = bNewIsLit;
	PointLight->SetVisibility(bIsLit);
	FlameVFX->SetVisibility(bIsLit);

	if (PuzzleManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s CheckPuzzle"), *GetName());
		PuzzleManager->CheckPuzzle();
	}
}

void ATorch::Interact(ADunegonEscapeCharacter* Character)
{
	SetLit(!bIsLit);
}

int32 ATorch::GetPuzzleState() const
{
	return bIsLit ? 1 : 0;
}