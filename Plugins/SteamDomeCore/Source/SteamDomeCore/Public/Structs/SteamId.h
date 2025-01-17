﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <steam/steam_api_common.h>
#include "SteamId.generated.h"


USTRUCT(BlueprintType)
struct STEAMDOMECORE_API FSteamId
{
	GENERATED_BODY()

protected:
	
	CSteamID UnderlyingSteamID;

public:

	FSteamId()
		: UnderlyingSteamID(k_steamIDNil)
		{}

	FSteamId(const CSteamID& SteamId)
		: UnderlyingSteamID(SteamId)
		{}
	
	FSteamId(const uint64 SteamId)
		: UnderlyingSteamID(CSteamID(SteamId))
		{}

	bool operator==(const FSteamId& Other) const
	{
		return UnderlyingSteamID == Other.UnderlyingSteamID;
	}

	static FSteamId FromUniqueNetId(const FUniqueNetIdRef& UniqueNetId);
	static FSteamId FromUniqueNetId(const FUniqueNetIdPtr& UniqueNetId);
	static FSteamId FromString(const FString& SteamId);
	static FSteamId FromUInt64(const uint64 SteamId);
	static FSteamId FromCSteamID(const CSteamID& SteamId);

	const CSteamID& GetCSteamID() const;
	CSteamID& GetCSteamID();

	uint64 ToUInt64() const;

	FString ToString() const;
	
	bool IsValid() const;
};

FORCEINLINE uint32 GetTypeHash(const FSteamId& Other)
{
	return GetTypeHash(Other.ToUInt64());
}
