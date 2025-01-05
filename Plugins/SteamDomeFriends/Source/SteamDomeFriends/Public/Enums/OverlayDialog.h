#pragma once

#include "CoreMinimal.h"
#include "OverlayDialog.generated.h"


UENUM(BlueprintType)
enum class EOverlayDialogSelf : uint8
{
	Friends = 0,
	Community = 1,
	Players = 2,
	Settings = 3,
	OfficialGameGroup = 4,
	Stats = 5,
	Achievements = 6,
};


UENUM(BlueprintType)
enum class EOverlayDialogUser : uint8
{
	SteamId = 0,
	Chat = 1,
	JoinTrade = 2,
	Stats = 3,
	Achievements = 4,
	FriendAdd = 5,
	FriendRemove = 6,
	FriendRequestAccept = 7,
	FriendRequestIgnore = 8,
};

inline const char* OverlayDialogSelfToCharPtr(const EOverlayDialogSelf OverlayDialog)
{
	switch (OverlayDialog)
	{
		case EOverlayDialogSelf::Friends:
			return "friends";
		case EOverlayDialogSelf::Community:
			return "community";
		case EOverlayDialogSelf::Players:
			return "players";
		case EOverlayDialogSelf::Settings:
			return "settings";
		case EOverlayDialogSelf::OfficialGameGroup:
			return "officialgamegroup";
		case EOverlayDialogSelf::Stats:
			return "stats";
		case EOverlayDialogSelf::Achievements:
			return "achievements";
	}

	checkNoEntry()
	return "";
}

inline const char* OverlayDialogUserToCharPtr(const EOverlayDialogUser OverlayDialog)
{
	switch (OverlayDialog)
	{
	case EOverlayDialogUser::SteamId:
		return "steamid";
	case EOverlayDialogUser::Chat:
		return "chat";
	case EOverlayDialogUser::JoinTrade:
		return "jointrade";
	case EOverlayDialogUser::Stats:
		return "stats";
	case EOverlayDialogUser::Achievements:
		return "achievements";
	case EOverlayDialogUser::FriendAdd:
		return "friendadd";
	case EOverlayDialogUser::FriendRemove:
		return "friendremove";
	case EOverlayDialogUser::FriendRequestAccept:
		return "friendrequestaccept";
	case EOverlayDialogUser::FriendRequestIgnore:
		return "friendrequestignore";
	}

	checkNoEntry()
	return "";
}
