// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndGameTrigger.generated.h"

class UBoxComponent;
class UPrimitiveComponent;
class UUserWidget;
class USceneComponent;

UCLASS()
class DUNEGONESCAPE_API AEndGameTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AEndGameTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> EndGameWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> EndGameWidget;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};