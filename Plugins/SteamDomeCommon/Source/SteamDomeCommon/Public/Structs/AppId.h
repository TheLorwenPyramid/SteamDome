// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <steam/steamtypes.h>
#include "AppId.generated.h"

USTRUCT(BlueprintType)
struct STEAMDOMECOMMON_API FAppId
{
	GENERATED_BODY()

	uint32 AppId;
	
	FAppId()
		: AppId(k_uAppIdInvalid)
		{}
	
	FAppId(const AppId_t AppId)
		: AppId(AppId)
		{}
};
