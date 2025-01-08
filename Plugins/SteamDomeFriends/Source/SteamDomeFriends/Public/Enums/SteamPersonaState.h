#pragma once

#include "CoreMinimal.h"
#include "SteamPersonaState.generated.h"


/**
 * List of states a Steam friend can be in.
 */
UENUM(BlueprintType)
enum class ESteamPersonaState : uint8
{
	Offline = 0, 			// Friend is not currently logged on.
	Online = 1, 			// Friend is logged on.
	Busy = 2, 				// Friend is logged on, but set to "Do not disturb."
	Away = 3, 				// Auto-away feature.
	Snooze = 4, 			// Auto-away for a long time.
	LookingToTrade = 5,		// Online, trading.
	LookingToPlay = 6, 		// Online, wanting to play.
	Max = 7 UMETA(Hidden),	// The total number of states. Only used for looping and validation.
};


namespace SteamPersonaState
{
	inline EPersonaState STEAMDOMEFRIENDS_API ToSteamEnum(const ESteamPersonaState SteamFriendRelationship)
	{
		return StaticCast<EPersonaState>(SteamFriendRelationship);
	}

	inline ESteamPersonaState STEAMDOMEFRIENDS_API FromSteamEnum(const EPersonaState SteamFriendRelationship)
	{
		return StaticCast<ESteamPersonaState>(SteamFriendRelationship);
	}
}

