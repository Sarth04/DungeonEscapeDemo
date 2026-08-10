// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#include "InteractionComponent.h"
#include "DunegonEscapeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Interactable.h"
#include "Blueprint/UserWidget.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ADunegonEscapeCharacter>(GetOwner());

	if (!Character)
	{
		UE_LOG(LogTemp, Error, TEXT("InteractionComponent: Owner is not a DunegonEscapeCharacter!"));
		return;
	}

	FirstPersonCameraComponent = Character->GetFirstPersonCameraComponent();

	if (!FirstPersonCameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InteractionComponent: Camera not found!"));
		return;
	}

	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionWidgetClass);

		if (InteractionWidget)
		{
			InteractionWidget->AddToViewport();
			InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckInteractionTarget();
	UpdateCurrentInteractableState();
}

void UInteractionComponent::SetCurrentInteractable(AInteractable* NewInteractable)
{
	if (CurrentInteractable == NewInteractable)
	{
		return;
	}

	if (bCurrentCanInteract && CurrentInteractable)
	{
		CurrentInteractable->OnFocusEnd();
	}

	CurrentInteractable = NewInteractable;

	bCurrentCanInteract = CurrentInteractable && CurrentInteractable->CanInteract();

	SetInteractionWidgetVisible(bCurrentCanInteract);

	if (bCurrentCanInteract)
	{
		CurrentInteractable->OnFocusBegin();
	}
}

void UInteractionComponent::CheckInteractionTarget()
{
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * MaxInteractionDistance);
	FCollisionShape InteractionSphere = FCollisionShape::MakeSphere(InteractionSphereRadius);

	FHitResult HitResult;
	const bool bHasHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, InteractionSphere);

	if (bHasHit)
	{
		SetCurrentInteractable(Cast<AInteractable>(HitResult.GetActor()));
	}
	else
	{
		SetCurrentInteractable(nullptr);
	}
}

void UInteractionComponent::UpdateCurrentInteractableState()
{
	if (!CurrentInteractable)
	{
		return;
	}

	const bool bCanInteract = CurrentInteractable->CanInteract();

	if (bCanInteract == bCurrentCanInteract)
	{
		return;
	}

	bCurrentCanInteract = bCanInteract;

	SetInteractionWidgetVisible(bCanInteract);

	if (bCanInteract)
	{
		UE_LOG(LogTemp, Warning, TEXT("FocusBegin"));
		CurrentInteractable->OnFocusBegin();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FocusEnd"));
		CurrentInteractable->OnFocusEnd();
	}
}

void UInteractionComponent::SetInteractionWidgetVisible(bool bVisible)
{
	if (!InteractionWidget)
	{
		return;
	}

	InteractionWidget->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UInteractionComponent::Interact()
{
	if (!CurrentInteractable || !CurrentInteractable->CanInteract())
	{
		return;
	}

	CurrentInteractable->Interact(Character);

	SetCurrentInteractable(nullptr);
	CheckInteractionTarget();
}