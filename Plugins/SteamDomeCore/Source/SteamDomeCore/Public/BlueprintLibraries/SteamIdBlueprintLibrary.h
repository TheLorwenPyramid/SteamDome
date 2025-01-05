// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/SteamId.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SteamIdBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class STEAMDOMECORE_API USteamIdBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName="Create SteamId From String")
	static FSteamId CreateSteamIdFromString(const FString& SteamIdString);

	UFUNCTION(BlueprintPure, DisplayName="Convert SteamId To String", meta=(BlueprintAutocast))
	static FString ConvertSteamIdToString(const FSteamId& SteamId);
};
