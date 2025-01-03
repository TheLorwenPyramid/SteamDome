// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UInt64.generated.h"

USTRUCT(BlueprintType)
struct STEAMDOMECOMMON_API FUInt64
{
	GENERATED_BODY()

	uint64 Value;
	
	FUInt64() = default;
	
	FUInt64(const uint64 Value)
		: Value(Value)
		{}
};
