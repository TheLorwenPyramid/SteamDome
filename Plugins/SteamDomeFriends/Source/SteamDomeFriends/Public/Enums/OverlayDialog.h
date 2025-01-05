#pragma once

#include "CoreMinimal.h"
#include "OverlayDialog.generated.h"

/**
 * Replaces Steam's string values with enums.
 * 
 * C++ only: These enums can be transformed into const char* using EOverlayDialogHelper
 */
UENUM(BlueprintType)
enum class EOverlayDialogSelf : uint8
{
	Friends = 0,
	Community = 1,
	Players = 2,
	Settings = 3,
	OfficialGameGroup = 4,
	Stats = 5,
	Achievements = 6,
};

/**
 * Replaces Steam's string values with enums.
 * 
 * C++ only: These enums can be transformed back into const char* using EOverlayDialogHelper
 */
UENUM(BlueprintType)
enum class EOverlayDialogUser : uint8
{
	SteamId = 0,
	Chat = 1,
	JoinTrade = 2,
	Stats = 3,
	Achievements = 4,
	FriendAdd = 5,
	FriendRemove = 6,
	FriendRequestAccept = 7,
	FriendRequestIgnore = 8,
};


namespace EOverlayDialogHelper
{
	STEAMDOMEFRIENDS_API const char* OverlayDialogSelfToCharPtr(const EOverlayDialogSelf OverlayDialog);
	
	STEAMDOMEFRIENDS_API const char* OverlayDialogUserToCharPtr(const EOverlayDialogUser OverlayDialog);
}

