// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <steam/steamtypes.h>
#include "AppId.generated.h"


/**
 * Represents an AppId_t (uint32) in Blueprints.
 */
USTRUCT(BlueprintType)
struct STEAMDOMECORE_API FAppId
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
