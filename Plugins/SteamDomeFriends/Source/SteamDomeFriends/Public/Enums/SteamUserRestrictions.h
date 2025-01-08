#pragma once

#include "CoreMinimal.h"
#include "SteamUserRestrictions.generated.h"


/**
 * User restriction flags. These are returned by GetUserRestrictions.
 *
 * @note Can be used as a bitfield in C++.
 */
UENUM(BlueprintType)
enum class ESteamUserRestriction : uint8
{
	None = 0,	 		//	No known chat/content restriction.
	Unknown = 1, 		//	We don't know yet, the user is offline.
	AnyChat = 2, 		//	User is not allowed to (or can't) send/recv any chat.
	VoiceChat = 4, 		//	User is not allowed to (or can't) send/recv voice chat.
	GroupChat = 8, 		//	User is not allowed to (or can't) send/recv group chat.
	Rating = 16, 		//	User is too young according to rating in current region.
	GameInvites = 32, 	//	User cannot send or recv game invites, for example if they are on mobile.
	Trading = 64, 		//	User cannot participate in trading, for example if they are on a console or mobile.
};


namespace SteamUserRestriction
{
	/** Converts a Bitfield in to a Set of ESteamUserRestriction */
	STEAMDOMEFRIENDS_API TSet<ESteamUserRestriction> ConvertBitfieldToSteamUserRestrictions(const int32 Bitfield);

	/** Converts a Set of ESteamUserRestriction in to a Bitfield */
	STEAMDOMEFRIENDS_API int32 ConvertSteamUserRestrictionsToBitfield(const TSet<ESteamUserRestriction>& Set);
}
