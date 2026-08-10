// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#include "EndGameTrigger.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "DunegonEscapeCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Components/SceneComponent.h"
#include "DiscordWebhookSubsystem.h"

AEndGameTrigger::AEndGameTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AEndGameTrigger::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEndGameTrigger::OnOverlapBegin);
}

void AEndGameTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADunegonEscapeCharacter* Character = Cast<ADunegonEscapeCharacter>(OtherActor);

	if (!Character)
	{
		return;
	}

	if (!EndGameWidgetClass)
	{
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());

	if (!PlayerController)
	{
		return;
	}

	EndGameWidget = CreateWidget<UUserWidget>(PlayerController, EndGameWidgetClass);

	if (!EndGameWidget)
	{
		return;
	}

	EndGameWidget->AddToViewport();

	Character->DisableInput(PlayerController);

	//Send a message to Discord webhook
	UDiscordWebhookSubsystem* Discord = GetGameInstance()->GetSubsystem<UDiscordWebhookSubsystem>();
	if (Discord)
	{
		Discord->SendMessage(TEXT("Game Completed"), true);
	}

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(EndGameWidget->TakeWidget());
	PlayerController->SetInputMode(InputMode);

	TriggerBox->SetGenerateOverlapEvents(false);
}