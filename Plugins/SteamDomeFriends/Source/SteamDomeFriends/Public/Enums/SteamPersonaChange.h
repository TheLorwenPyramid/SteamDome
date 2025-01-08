#pragma once


#include "CoreMinimal.h"
#include <steam/isteamfriends.h>
#include "SteamPersonaChange.generated.h"


/**
 * Replaces Steam's string values with enums.
 * 
 * C++ only: These enums can be transformed into const char* using EOverlayDialogHelper
 */
UENUM(BlueprintType)
enum class ESteamPersonaChange : uint8
{
	INVALID = 0, // Do not use, Unreal requires a 0 value for default initialization of enums.
	Name = 1,
	Status = 2,
	ComeOnline = 3,
	GoneOffline	= 4,
	GamePlayed = 5,
	GameServer = 6,
	Avatar = 7,
	JoinedSource = 8,
	LeftSource = 9,
	RelationshipChanged = 10,
	NameFirstSet = 11,
	Broadcast = 12,
	Nickname =	13,
	SteamLevel = 14,
	RichPresence = 15,
};


namespace PersonaChange
{
	STEAMDOMEFRIENDS_API EPersonaChange ToSteamEnum(const ESteamPersonaChange PersonaChange);
	
	STEAMDOMEFRIENDS_API bool HasBitEnabled(const int32 Bitfield, const ESteamPersonaChange PersonaChange);
}
