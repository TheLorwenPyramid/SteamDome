// Fill out your copyright notice in the Description page of Project Settings.


#include "Enums/OverlayDialog.h"


const char* EOverlayDialogHelper::OverlayDialogSelfToCharPtr(const EOverlayDialogSelf OverlayDialog)
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


const char* EOverlayDialogHelper::OverlayDialogUserToCharPtr(const EOverlayDialogUser OverlayDialog)
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
