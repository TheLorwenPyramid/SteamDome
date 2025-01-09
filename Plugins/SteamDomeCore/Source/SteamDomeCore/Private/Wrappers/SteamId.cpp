// Fill out your copyright notice in the Description page of Project Settings.

#include "Structs/SteamId.h"

#include <steam/steam_api.h>
#include "Kismet/KismetStringLibrary.h"


FSteamId FSteamId::FromUniqueNetId(const FUniqueNetIdRef& UniqueNetId)
{
	return FromString(UniqueNetId->ToString());
}


FSteamId FSteamId::FromUniqueNetId(const FUniqueNetIdPtr& UniqueNetId)
{
	return FromString(UniqueNetId->ToString());
}


FSteamId FSteamId::FromString(const FString& SteamId)
{
	const uint64 SteamId64 = UKismetStringLibrary::Conv_StringToInt64(SteamId);
	return FromUInt64(SteamId64);
}


FSteamId FSteamId::FromUInt64(const uint64 SteamId)
{
	return FSteamId(SteamId);
}


FSteamId FSteamId::FromCSteamID(const CSteamID& SteamId)
{
	return FSteamId(SteamId);
}


const CSteamID& FSteamId::GetCSteamID() const
{
	return UnderlyingSteamID;
}


CSteamID& FSteamId::GetCSteamID()
{
	return UnderlyingSteamID;
}


uint64 FSteamId::ToUInt64() const
{
	return UnderlyingSteamID.ConvertToUint64();
}


FString FSteamId::ToString() const
{
	return FString::Printf(TEXT("%llu"), UnderlyingSteamID.ConvertToUint64());
}


bool FSteamId::IsValid() const
{
	return UnderlyingSteamID.IsValid();
}
