// Fill out your copyright notice in the Description page of Project Settings.


#include "Enums/SteamFriendFlags.h"

#include <steam/isteamfriends.h>


#define AS_INT(Value) static_cast<int32>(Value)

int32 ConvertSteamFriendFlagsToBitfield(const ESteamFriendFlags Flags)
{
	const int32 FlagsIn = StaticCast<int32>(Flags);
	int32 OutFlags = 0;

	/*
	if (FlagsIn & 0x00) OutFlags |= static_cast<int32_t>(EFriendFlags::k_EFriendFlagNone);
	if (FlagsIn & 0x01) OutFlags |= static_cast<int32_t>(EFriendFlags::k_EFriendFlagBlocked);
	if (FlagsIn & 0x02) OutFlags |= static_cast<int32_t>(EFriendFlags::k_EFriendFlagFriendshipRequested);
	if (FlagsIn & 0x03) OutFlags |= static_cast<int32_t>(EFriendFlags::k_EFriendFlagImmediate);
	if (FlagsIn & 0x04) OutFlags |= static_cast<int32_t>(EFriendFlags::k_EFriendFlagClanMember);
	if (FlagsIn & 0x05) OutFlags |= static_cast<int32_t>(EFriendFlags::k_EFriendFlagOnGameServer);
	if (FlagsIn & 0x06) OutFlags |= static_cast<int32_t>(EFriendFlags::k_EFriendFlagRequestingFriendship);
	if (FlagsIn & 0x07) OutFlags |= static_cast<int32_t>(EFriendFlags::k_EFriendFlagRequestingInfo);
	if (FlagsIn & 0x08) OutFlags |= static_cast<int32_t>(EFriendFlags::k_EFriendFlagIgnored);
	if (FlagsIn & 0x09) OutFlags |= static_cast<int32_t>(EFriendFlags::k_EFriendFlagIgnoredFriend);
	if (FlagsIn & 0x10) OutFlags |= static_cast<int32_t>(EFriendFlags::k_EFriendFlagChatMember);
	if (FlagsIn & 0x11) OutFlags |= static_cast<int32_t>(EFriendFlags::k_EFriendFlagAll);
	*/

	OutFlags |= (FlagsIn & 0x00) & AS_INT(EFriendFlags::k_EFriendFlagNone);
	OutFlags |= (FlagsIn & 0x01) & AS_INT(EFriendFlags::k_EFriendFlagBlocked);
	OutFlags |= (FlagsIn & 0x02) & AS_INT(EFriendFlags::k_EFriendFlagFriendshipRequested);
	OutFlags |= (FlagsIn & 0x03) & AS_INT(EFriendFlags::k_EFriendFlagImmediate);
	OutFlags |= (FlagsIn & 0x04) & AS_INT(EFriendFlags::k_EFriendFlagClanMember);
	OutFlags |= (FlagsIn & 0x05) & AS_INT(EFriendFlags::k_EFriendFlagOnGameServer);
	OutFlags |= (FlagsIn & 0x06) & AS_INT(EFriendFlags::k_EFriendFlagRequestingFriendship);
	OutFlags |= (FlagsIn & 0x07) & AS_INT(EFriendFlags::k_EFriendFlagRequestingInfo);
	OutFlags |= (FlagsIn & 0x08) & AS_INT(EFriendFlags::k_EFriendFlagIgnored);
	OutFlags |= (FlagsIn & 0x09) & AS_INT(EFriendFlags::k_EFriendFlagIgnoredFriend);
	OutFlags |= (FlagsIn & 0x0A) & AS_INT(EFriendFlags::k_EFriendFlagChatMember);
	OutFlags |= (FlagsIn & 0xFF) & AS_INT(EFriendFlags::k_EFriendFlagAll);

	return OutFlags;
}


int32 ConvertSteamFriendFlagsSetToBitfield(const TSet<ESteamFriendFlags>& Flags)
{
	int32 SteamFlag = 0;

	if (Flags.Contains(ESteamFriendFlags::All))
	{
		return EFriendFlags::k_EFriendFlagAll;
	}

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
