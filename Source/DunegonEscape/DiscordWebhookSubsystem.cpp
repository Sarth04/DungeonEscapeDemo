// Copyright (c) 2026 Marcin Pryczek. All Rights Reserved.


#include "DiscordWebhookSubsystem.h"
#include "DiscordSettings.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/Guid.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "GeneralProjectSettings.h"

void UDiscordWebhookSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	StartTime = FPlatformTime::Seconds();

	SendMessage(TEXT("Game Started"), false);
}

void UDiscordWebhookSubsystem::SendMessage(const FString& Message, bool bIncludePlayTime)
{
	const UDiscordSettings* Settings = GetDefault<UDiscordSettings>();
	if (!Settings || Settings->WebhookUrl.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Discord webhook URL is not set."));
		return;
	}

	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = CreateRequest(Settings->WebhookUrl);
	const FString FinalMessage = BuildMessage(Message, bIncludePlayTime);
	const FString Json = BuildJson(FinalMessage);

	Request->SetContentAsString(Json);
	if (!Request->ProcessRequest())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to send Discord webhook."));
	}
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> UDiscordWebhookSubsystem::CreateRequest(const FString& Url) const
{
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	return Request;
}

FString UDiscordWebhookSubsystem::BuildMessage(const FString& Message, bool bIncludePlayTime) const
{
	const FString InstallationId = GetInstallationId();
	const FString Version = GetDefault<UGeneralProjectSettings>()->ProjectVersion;
	FString FinalMessage = FString::Printf(TEXT("%s\nInstallation: %s\nVersion: %s"), *Message, *InstallationId, *Version);

	if (bIncludePlayTime)
	{
		const int32 TotalSeconds = FMath::RoundToInt(GetPlayTime());
		const int32 Minutes = TotalSeconds / 60;
		const int32 Seconds = TotalSeconds % 60;
		FinalMessage += FString::Printf(TEXT("\nPlay Time: %02d:%02d"), Minutes, Seconds);
	}
	return FinalMessage;
}

FString UDiscordWebhookSubsystem::BuildJson(const FString& Message) const
{
	const TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(TEXT("content"), Message);
	FString Json;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Json);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	return Json;
}

FString UDiscordWebhookSubsystem::GetInstallationId() const
{
	FString InstallationId;

	if (GConfig->GetString(TEXT("Discord"), TEXT("InstallationId"), InstallationId, GGameIni))
	{
		return InstallationId;
	}

	InstallationId = FGuid::NewGuid().ToString(EGuidFormats::Digits);

	GConfig->SetString(TEXT("Discord"), TEXT("InstallationId"), *InstallationId, GGameIni);

	GConfig->Flush(false, GGameIni);

	return InstallationId;
}

double UDiscordWebhookSubsystem::GetPlayTime() const
{
	return FPlatformTime::Seconds() - StartTime;
}