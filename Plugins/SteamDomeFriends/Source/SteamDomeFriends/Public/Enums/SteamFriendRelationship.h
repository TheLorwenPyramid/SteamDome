#pragma once

#include "CoreMinimal.h"
#include "SteamFriendRelationship.generated.h"


/**
 * Declares the set of relationships that Steam users may have.
 */
UENUM(BlueprintType)
enum class ESteamFriendRelationship : uint8
{
	None = 0, 					//	The users have no relationship.
	Blocked = 1, 				//	The user has just clicked Ignore on an friendship invite. This doesn't get stored.
	RequestRecipient = 2, 		//	The user has requested to be friends with the current user.
	Friend = 3, 				//	A "regular" friend.
	RequestInitiator = 4, 		//	The current user has sent a friend invite.
	Ignored = 5, 				//	The current user has explicit blocked this other user from comments/chat/etc. This is stored.
	IgnoredFriend = 6, 			//	The user has ignored the current user.
	Suggested_DEPRECATED = 7, 	//	Deprecated -- Unused.
	Max = 8 UMETA(Hidden),		//	The total number of friend relationships used for looping and verification.
};
