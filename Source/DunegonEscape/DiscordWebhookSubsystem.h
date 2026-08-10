// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DiscordWebhookSubsystem.generated.h"

class IHttpRequest;
class UDiscordSettings;

UCLASS()
class DUNEGONESCAPE_API UDiscordWebhookSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void SendMessage(const FString& Message, bool bIncludePlayTime);

private:

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> CreateRequest(const FString& Url) const;
    FString BuildMessage(const FString& Message, bool bIncludePlayTime) const;
    FString BuildJson(const FString& Message) const;

    FString GetInstallationId() const;
    double GetPlayTime() const;

private:

    double StartTime = 0.0;
};
