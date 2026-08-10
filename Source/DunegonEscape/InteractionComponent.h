// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AInteractable;
class ADunegonEscapeCharacter;
class UCameraComponent;
class UUserWidget;

UCLASS()
class DUNEGONESCAPE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();

	void Interact();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime,ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;

private:
	void CheckInteractionTarget();
	void SetCurrentInteractable(AInteractable* NewInteractable);
	void SetInteractionWidgetVisible(bool bVisible);
	void UpdateCurrentInteractableState();

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float MaxInteractionDistance = 300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionSphereRadius = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> InteractionWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> InteractionWidget = nullptr;

	UPROPERTY()
	TObjectPtr<ADunegonEscapeCharacter> Character = nullptr;

	UPROPERTY()
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent = nullptr;

	UPROPERTY()
	TObjectPtr<AInteractable> CurrentInteractable = nullptr;

	bool bCurrentCanInteract = false;
};