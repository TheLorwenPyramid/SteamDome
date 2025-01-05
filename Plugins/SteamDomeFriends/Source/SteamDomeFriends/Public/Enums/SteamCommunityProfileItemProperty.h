#pragma once

#include "CoreMinimal.h"
#include "SteamCommunityProfileItemType.h"
#include "SteamCommunityProfileItemProperty.generated.h"


/**
 * Properties on a Steam Community profile item. See GetProfileItemPropertyString and GetProfileItemPropertyUint.
 */
UENUM(BlueprintType)
enum class ESteamCommunityProfileItemProperty : uint8
{
	ImageSmall = 0, 		//	URL to the small or animated version of the image
	ImageLarge = 1, 		//	URL to the large or static version of the image
	InternalName = 2, 		//	Internal name entered on the partner site (for debugging)
	Title = 3, 				//	Localized name of the item
	Description = 4, 		//	Localized description of the item
	AppID = 5, 				//	AppID of the item (unsigned integer)
	TypeID = 6, 			//	Type id of the item, unique to the appid (unsigned integer)
	Class = 7, 				//	"Class" or type of item (internal value, unsigned integer)
	MovieWebM = 8, 			//	URL to the webm video file
	MovieMP4 = 9, 			//	URL to the mp4 video file
	MovieWebMSmall = 10, 	//	URL to the small webm video file
	MovieMP4Small = 11, 	//	URL to the small mp4 video file
};


namespace ESteamCommunityProfileItemPropertyHelper
{
	inline ECommunityProfileItemProperty ToSteamEnum(const ESteamCommunityProfileItemProperty OurEnum)
	{
		return StaticCast<ECommunityProfileItemProperty>(OurEnum);
	}
};

