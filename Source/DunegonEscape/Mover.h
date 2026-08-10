// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNEGONESCAPE_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:
	UMover();

	void SetActivated(bool bActivated);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void UpdateAlpha(float DeltaTime);
	void UpdateLocation();
	void UpdateRotation();

	UPROPERTY()
	TObjectPtr<AActor> Owner = nullptr;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector TranslationOffset;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FRotator RotationOffset;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0.01"))
	float MovementDuration = 2.f;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FRotator StartRotation;

	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY()
	FRotator TargetRotation;

	UPROPERTY()
	float CurrentAlpha = 0.f;

	UPROPERTY()
	bool bIsActivated = false;
};
