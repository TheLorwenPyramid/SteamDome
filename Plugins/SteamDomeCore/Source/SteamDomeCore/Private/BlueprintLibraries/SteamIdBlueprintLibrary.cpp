// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintLibraries/SteamIdBlueprintLibrary.h"


FSteamId USteamIdBlueprintLibrary::CreateSteamIdFromString(const FString& SteamIdString)
{
	return FSteamId::FromString(SteamIdString);
}


FString USteamIdBlueprintLibrary::ConvertSteamIdToString(const FSteamId& SteamId)
{
	return SteamId.ToString();
}
