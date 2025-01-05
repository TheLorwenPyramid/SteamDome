// Fill out your copyright notice in the Description page of Project Settings.


#include "Enums/SteamFriendFlags.h"

#include <steam/isteamfriends.h>


#define AS_INT(Value) static_cast<int32>(Value)


int32 ConvertSteamFriendFlagsSetToBitfield(const TSet<ESteamFriendFlags>& Flags)
{
	if (Flags.Contains(ESteamFriendFlags::All))
	{
		return EFriendFlags::k_EFriendFlagAll;
	}

	int32 SteamFlag = 0;

	// CAREFUL!!
	// This is needed as UENUMs are uint8 while the original EFriendFlags is int32
	// so the values between EFriendFlags and ESteamFriendFlags are not compatible.
	// This loop should transform correctly between the two.
	for (const auto Flag : Flags)
	{
		switch (Flag) {
		case ESteamFriendFlags::None:
			SteamFlag |= AS_INT(EFriendFlags::k_EFriendFlagNone);
			break;
		case ESteamFriendFlags::Blocked:
			SteamFlag |= AS_INT(EFriendFlags::k_EFriendFlagBlocked);
			break;
		case ESteamFriendFlags::FriendshipRequested:
			SteamFlag |= AS_INT(EFriendFlags::k_EFriendFlagFriendshipRequested);
			break;
		case ESteamFriendFlags::Immediate:
			SteamFlag |= AS_INT(EFriendFlags::k_EFriendFlagImmediate);
			break;
		case ESteamFriendFlags::ClanMember:
			SteamFlag |= AS_INT(EFriendFlags::k_EFriendFlagClanMember);
			break;
		case ESteamFriendFlags::OnGameServer:
			SteamFlag |= AS_INT(EFriendFlags::k_EFriendFlagOnGameServer);
			break;
		case ESteamFriendFlags::RequestingFriendship:
			SteamFlag |= AS_INT(EFriendFlags::k_EFriendFlagRequestingFriendship);
			break;
		case ESteamFriendFlags::RequestingInfo:
			SteamFlag |= AS_INT(EFriendFlags::k_EFriendFlagRequestingInfo);
			break;
		case ESteamFriendFlags::Ignored:
			SteamFlag |= AS_INT(EFriendFlags::k_EFriendFlagIgnored);
			break;
		case ESteamFriendFlags::IgnoredFriend:
			SteamFlag |= AS_INT(EFriendFlags::k_EFriendFlagIgnoredFriend);
			break;
		case ESteamFriendFlags::ChatMember:
			SteamFlag |= AS_INT(EFriendFlags::k_EFriendFlagChatMember);
			break;
		case ESteamFriendFlags::All:
			SteamFlag |= AS_INT(EFriendFlags::k_EFriendFlagAll);
			break;
		}
	}

	return SteamFlag;
}
