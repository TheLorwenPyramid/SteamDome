// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/GameId.h"
#include "Structs/SteamId.h"
#include "FriendGameInfo.generated.h"


struct FriendGameInfo_t;

/**
 * 
 */
USTRUCT(BlueprintType)
struct STEAMDOMEFRIENDS_API FFriendGameInfo
{
	GENERATED_BODY()

	/* The game ID that the friend is playing */
	UPROPERTY()
	FGameId GameId;
	
	/* The IP of the server the friend is playing on */
	UPROPERTY()
	int64 GameIP = -1;
	
	/* The port of the server the friend is playing on */
	UPROPERTY()
	int32 GamePort = -1;
	
	/* The query port of the server the friend is playing on */
	UPROPERTY()
	int32 QueryPort = -1;
	
	/* The Steam ID of the lobby the friend is in */
	UPROPERTY()
	FSteamId SteamIdLobby;
	
	FFriendGameInfo() = default;
	FFriendGameInfo(const FriendGameInfo_t& FriendGameInfo);
};
