// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintLibraries/SteamIdBlueprintLibrary.h"


FSteamId USteamIdBlueprintLibrary::FromString(const FString& SteamIdString)
{
	return FSteamId::FromString(SteamIdString);
}


FString USteamIdBlueprintLibrary::ToString(FSteamId SteamId)
{
	return SteamId.ToString();
}
