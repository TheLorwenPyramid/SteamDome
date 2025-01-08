#pragma once

#include "CoreMinimal.h"
#include "SteamOverlayToStoreFlag.generated.h"


/**
 * These values are passed as parameters to the store with ActivateGameOverlayToStore
 * and modify the behavior when the page opens.
 */
UENUM(BlueprintType)
enum class ESteamOverlayToStoreFlag : uint8
{
	None = 0, // No
	// AddToCart = 1, // Deprecated, now works the same as k_EOverlayToStoreFlag_AddToCartAndShow.
	AddToCharAndShow = 2, // Add the specified app ID to the users cart and show the store page.
};


namespace SteamOverlayToStoreFlag
{
	inline EOverlayToStoreFlag STEAMDOMEFRIENDS_API ToSteamEnum(const ESteamOverlayToStoreFlag SteamFriendRelationship)
	{
		return StaticCast<EOverlayToStoreFlag>(SteamFriendRelationship);
	}

	inline ESteamOverlayToStoreFlag STEAMDOMEFRIENDS_API FromSteamEnum(const EOverlayToStoreFlag SteamFriendRelationship)
	{
		return StaticCast<ESteamOverlayToStoreFlag>(SteamFriendRelationship);
	}
}
