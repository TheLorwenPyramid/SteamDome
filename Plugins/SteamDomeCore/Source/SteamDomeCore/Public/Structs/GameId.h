// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <steam/steam_api_common.h>
#include "GameId.generated.h"


USTRUCT(BlueprintType)
struct STEAMDOMECORE_API FGameId
{
	GENERATED_BODY()

protected:
	
	CGameID UnderlyingGameId;

public:

	FGameId() = default;

	FGameId(const CGameID& GameId)
		: UnderlyingGameId(GameId)
		{}

	static FGameId FromCGameID(const CGameID& GameId);

	const CGameID& GetGameId() const;
	CGameID& GetGameId();

	FString ToString() const;
	
	bool IsValid() const;
};
