#pragma once

#include "CoreMinimal.h"
#include "steam/isteamfriends.h"
#include "SteamCommunityProfileItemType.generated.h"


UENUM(BlueprintType)
enum class ESteamCommunityProfileItemType : uint8
{
	AnimatedAvatar = 0, 		// Animated avatar image (GIF)
	AvatarFrame = 1, 			// Avatar frame (may or may not be an animated PNG)
	ProfileModifier = 2, 		// Special profile modifier item, like Seasonal Profile or Artist Profile
	ProfileBackground = 3, 		// Profile background image or movie
	MiniProfileBackground = 4, 	// Background image or movie for the hover flyout for a user
};


namespace ESteamCommunityProfileItemTypeHelper
{
	inline ECommunityProfileItemType ToSteamEnum(const ESteamCommunityProfileItemType OurEnum)
	{
		return StaticCast<ECommunityProfileItemType>(OurEnum);
	}
};
