// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <steam/steam_api_common.h>
#include "SteamId.generated.h"


USTRUCT(BlueprintType)
struct STEAMDOMECOMMON_API FSteamId
{
	GENERATED_BODY()

protected:
	
	CSteamID UnderlyingSteamID;

	explicit FSteamId(const uint64 SteamId);
	explicit FSteamId(const CSteamID& SteamId);

public:

	FSteamId() = default;

	static FSteamId FromUniqueNetId(const FUniqueNetIdRef& UniqueNetId);
	static FSteamId FromUniqueNetId(const FUniqueNetIdPtr& UniqueNetId);
	static FSteamId FromString(const FString& SteamId);
	static FSteamId FromUInt64(const uint64 SteamId);
	static FSteamId FromCSteamID(const CSteamID& SteamId);

	const CSteamID& GetCSteamID() const;
	CSteamID& GetCSteamID();

	FString ToString() const;
	
	bool IsValid() const;
};
