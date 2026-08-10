// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DiscordSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Discord"))
class DUNEGONESCAPE_API UDiscordSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, Category = "Analytics")
	FString WebhookUrl;
};