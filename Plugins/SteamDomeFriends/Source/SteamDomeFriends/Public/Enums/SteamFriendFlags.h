#pragma once

#include "CoreMinimal.h"
#include "SteamFriendFlags.generated.h"


/**
 * Flags for enumerating friends list, or quickly checking the relationship between users.
 */
UENUM(BlueprintType)
enum class ESteamFriendFlags : uint8
{
	None = 0x0, 				 // None.
	Blocked = 0x01, 			 // Users that the current user has blocked from contacting.
	FriendshipRequested = 0x02,  // Users that have sent a friend invite to the current user.
	Immediate = 0x03, 			 // The current user's "regular" friends.
	ClanMember = 0x04, 			 // Users that are in one of the same (small) Steam groups as the current user.
	OnGameServer = 0x05, 		 // Users that are on the same game server; as set by SetPlayedWith.
	RequestingFriendship = 0x06, // Users that the current user has sent friend invites to.
	RequestingInfo = 0x07, 		 // Users that are currently sending additional info about themselves after a call to RequestUserInformation
	Ignored = 0x08, 			 // Users that the current user has ignored from contacting them.
	IgnoredFriend = 0x09, 		 // Users that have ignored the current user; but the current user still knows about them.
	ChatMember = 0x0A, 			 // Users in one of the same chats.
	All = 0xFF, 				 // Returns all friend flags.
};


namespace ESteamFriendFlagsHelper
{
	/**
	 * TODO: Probably these two functions can be improved using better techniques. For now it should do.
	 */

	/** Transforms a set of Flags into a bitfield */
	STEAMDOMEFRIENDS_API int32 ConvertSteamFriendFlagsSetToBitfield(const TSet<ESteamFriendFlags>& Flags);
}
