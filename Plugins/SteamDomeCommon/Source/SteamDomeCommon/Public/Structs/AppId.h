// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AppId.generated.h"

USTRUCT(BlueprintType)
struct STEAMDOMECOMMON_API FAppId
{
	GENERATED_BODY()

	uint32 AppId;
	
	FAppId() = default;
	
	FAppId(const uint32 AppId)
		: AppId(AppId)
		{}
};
