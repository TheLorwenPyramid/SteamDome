// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FriendsGroupId.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct STEAMDOMEFRIENDS_API FFriendsGroupId
{
	GENERATED_BODY()

protected:

	int16 Id;

public:

	FFriendsGroupId() = default;

	FFriendsGroupId(const int16 Id)
		: Id(Id)
		{}

	int16 GetId() const
		{ return Id; }
};
