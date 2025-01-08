// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <steam/steamtypes.h>
#include "DepotId.generated.h"


/**
 * Represents an DepotId_t (uint32) in Blueprints.
 */
USTRUCT(BlueprintType)
struct STEAMDOMECORE_API FDepotId
{
	GENERATED_BODY()

	uint32 DepotId = k_uDepotIdInvalid;
	
	FDepotId() = default;
	
	FDepotId(const uint32 DepotId)
		: DepotId(DepotId)
		{}
};
