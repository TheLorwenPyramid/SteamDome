// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClanActivityCounts.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct STEAMDOMEFRIENDS_API FClanActivityCounts
{
	GENERATED_BODY()
	
	/** Number of members that are online. */
	UPROPERTY(BlueprintReadOnly)
	int32 Online = -1;

	/** Number members that are in game (excluding those with their status set to offline). */
	UPROPERTY(BlueprintReadOnly)
	int32 InGame = -1;

	/** Number of members in the group chat room. */
	UPROPERTY(BlueprintReadOnly)
	int32 Chatting = -1;
	
	FClanActivityCounts() = default;

	FClanActivityCounts(const int32 InOnline, const int32 InInGame, const int32 InChatting)
		: Online(InOnline), InGame(InInGame), Chatting(InChatting)
		{}
};
