// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/SteamChatEntryType.h"
#include "ChatMessage.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct STEAMDOMEFRIENDS_API FChatMessage
{
	GENERATED_BODY()
	
	/** Message that was received */
	UPROPERTY(BlueprintReadOnly)
	FString Message;

	/** Type of chat entry that was received. */
	UPROPERTY(BlueprintReadOnly)
	ESteamChatEntryType MessageType = ESteamChatEntryType::Invalid;
	
	FChatMessage() = default;

	FChatMessage(const FString& InMessage, const ESteamChatEntryType InMessageType)
		: Message(InMessage), MessageType(InMessageType)
		{}
};
