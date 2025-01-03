// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DepotId.generated.h"

USTRUCT(BlueprintType)
struct STEAMDOMECOMMON_API FDepotId
{
	GENERATED_BODY()

	uint32 DepotId;
	
	FDepotId() = default;
	
	FDepotId(const uint32 DepotId)
		: DepotId(DepotId)
		{}
};


UCLASS()
class STEAMDOMECOMMON_API UDepotIdFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="SteamDome|Common", meta=(DisplayName="Convert To String", CompactNodeTitle="->", BlueprintAutocast))
	static FString DepotIdToString(const FDepotId& DepotId)
	{
		return FString::Printf(TEXT("%d"), DepotId.DepotId);
	}
};
