// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/SteamFriendsSubsystem.h"

#include <steam/isteamfriends.h>

#include "Enums/SteamFriendFlags.h"
#include "Helpers/TempString.h"
#include "Structs/ChatMessage.h"
#include "Structs/ClanActivityCounts.h"
#include "Structs/FriendGameInfo.h"


void USteamFriendsSubsystem::ActivateGameOverlay(const EOverlayDialogSelf OverlayDialog)
{
	SteamFriends()->ActivateGameOverlay(EOverlayDialogHelper::OverlayDialogSelfToCharPtr(OverlayDialog));
}


void USteamFriendsSubsystem::ActivateGameOverlayInviteDialog(const FSteamId SteamIDLobby)
{
	SteamFriends()->ActivateGameOverlayInviteDialog(SteamIDLobby.GetCSteamID());
}


void USteamFriendsSubsystem::ActivateGameOverlayToStore(const FAppId AppId, const ESteamOverlayToStoreFlag Flag)
{
	SteamFriends()->ActivateGameOverlayToStore(AppId.AppId, StaticCast<EOverlayToStoreFlag>(Flag));
}


void USteamFriendsSubsystem::ActivateGameOverlayToUser(const EOverlayDialogUser OverlayDialog, const FSteamId SteamId)
{
	SteamFriends()->ActivateGameOverlayToUser(
		EOverlayDialogHelper::OverlayDialogUserToCharPtr(OverlayDialog), SteamId.GetCSteamID()
	);
}


void USteamFriendsSubsystem::ActivateGameOverlayToWebPage(
	const FString& URL, const ESteamActivateGameOverlayToWebPageMode Mode
) {
	SteamFriends()->ActivateGameOverlayToWebPage(
		TCHAR_TO_UTF8(*URL), StaticCast<EActivateGameOverlayToWebPageMode>(Mode)
	);
}


void USteamFriendsSubsystem::ClearRichPresence()
{
	SteamFriends()->ClearRichPresence();
}


bool USteamFriendsSubsystem::CloseClanChatWindowInSteam(FSteamId SteamIdClanChat)
{
	return SteamFriends()->CloseClanChatWindowInSteam(SteamIdClanChat.GetCSteamID());
}


FSteamId USteamFriendsSubsystem::GetChatMemberByIndex(FSteamId SteamIdClan, int UserIndex)
{
	return SteamFriends()->GetChatMemberByIndex(SteamIdClan.GetCSteamID(), UserIndex);
}


bool USteamFriendsSubsystem::GetClanActivityCounts(FSteamId SteamIdClan, FClanActivityCounts& ClanActivityCounts)
{
	return SteamFriends()->GetClanActivityCounts(
		SteamIdClan.GetCSteamID(),
		&ClanActivityCounts.Online,
		&ClanActivityCounts.InGame,
		&ClanActivityCounts.Chatting
	);
}


bool USteamFriendsSubsystem::GetClanChatMessage(
	const FSteamId SteamIdClanChat,
	const int MessageIndex,
	FChatMessage& ChatMessage,
	FSteamId& SteamIdChatter,
	const int32 MaxMessageLength
) {
	const FTempString TempString(MaxMessageLength);

	EChatEntryType ChatEntry;
	CSteamID Chatter;
	
	const int32 Bytes = SteamFriends()->GetClanChatMessage(
		SteamIdClanChat.GetCSteamID(),
		MessageIndex,
		TempString.Start(),
		MaxMessageLength,
		&ChatEntry,
		&Chatter
	);

	// This should not be negative, but better safe than sorry
	if (Bytes <= 0)
	{
		return false;
	}

	ChatMessage.Message = TempString.ToString();
	ChatMessage.MessageType = StaticCast<ESteamChatEntryType>(ChatEntry);
	SteamIdChatter = FSteamId::FromCSteamID(Chatter);

	return true;
}


int32 USteamFriendsSubsystem::GetClanCount()
{
	return SteamFriends()->GetClanCount();
}


FString USteamFriendsSubsystem::GetClanName(const FSteamId& SteamIdClan)
{
	return SteamFriends()->GetClanName(SteamIdClan.GetCSteamID());
}


FSteamId USteamFriendsSubsystem::GetClanOfficerByIndex(const FSteamId SteamIdClan, const int32 Officer)
{
	return SteamFriends()->GetClanOfficerByIndex(SteamIdClan.GetCSteamID(), Officer);
}


int32 USteamFriendsSubsystem::GetClanOfficerCount(const FSteamId SteamIdClan)
{
	return SteamFriends()->GetClanOfficerCount(SteamIdClan.GetCSteamID());
}


FSteamId USteamFriendsSubsystem::GetClanOwner(const FSteamId SteamIdClan)
{
	return SteamFriends()->GetClanOwner(SteamIdClan.GetCSteamID());
}


FString USteamFriendsSubsystem::GetClanTag(const FSteamId SteamIdClan)
{
	return SteamFriends()->GetClanTag(SteamIdClan.GetCSteamID());
}


FSteamId USteamFriendsSubsystem::GetCoplayFriend(int32 CoplayFriendIndex)
{
	return SteamFriends()->GetCoplayFriend(CoplayFriendIndex);
}


int32 USteamFriendsSubsystem::GetCoplayFriendCount()
{
	return SteamFriends()->GetCoplayFriendCount();
}


FSteamId USteamFriendsSubsystem::GetFriendByIndex(const int32 FriendIndex, const TSet<ESteamFriendFlags>& FriendFlags)
{
	return GetFriendByIndex(FriendIndex, ESteamFriendFlagsHelper::ConvertSteamFriendFlagsSetToBitfield(FriendFlags));
}


FSteamId USteamFriendsSubsystem::GetFriendByIndex(const int32 FriendIndex, const int32 FriendFlags)
{
	return SteamFriends()->GetFriendByIndex(FriendIndex, FriendFlags);
}


FAppId USteamFriendsSubsystem::GetFriendCoplayGame(FSteamId SteamIdFriend)
{
	return SteamFriends()->GetFriendCoplayGame(SteamIdFriend.GetCSteamID());
}


int32 USteamFriendsSubsystem::GetFriendCoplayTime(FSteamId SteamIdFriend)
{
	return SteamFriends()->GetFriendCoplayTime(SteamIdFriend.GetCSteamID());
}


int32 USteamFriendsSubsystem::GetFriendCount(const int32 FriendFlags)
{
	return SteamFriends()->GetFriendCount(FriendFlags);
}


int32 USteamFriendsSubsystem::GetFriendCountFromSource(const FSteamId SteamIdSource)
{
	return SteamFriends()->GetFriendCountFromSource(SteamIdSource.GetCSteamID());
}


FSteamId USteamFriendsSubsystem::GetFriendFromSourceByIndex(const FSteamId SteamIdSource, const int32 FriendIndex)
{
	return SteamFriends()->GetFriendFromSourceByIndex(SteamIdSource.GetCSteamID(), FriendIndex);
}


bool USteamFriendsSubsystem::GetFriendGamePlayed(const FSteamId SteamIdFriend, FFriendGameInfo& FriendGameInfo)
{
	FriendGameInfo_t SteamFriendGameInfo;
	const bool bSuccess = SteamFriends()->GetFriendGamePlayed(SteamIdFriend.GetCSteamID(), &SteamFriendGameInfo);

	if (!bSuccess)
	{
		return bSuccess;
	}

	FriendGameInfo.GameId = SteamFriendGameInfo.m_gameID;
	FriendGameInfo.GamePort = SteamFriendGameInfo.m_usGamePort;
	FriendGameInfo.QueryPort = SteamFriendGameInfo.m_usQueryPort;
	FriendGameInfo.GameIP = SteamFriendGameInfo.m_unGameIP;
	FriendGameInfo.SteamIdLobby = SteamFriendGameInfo.m_steamIDLobby;

	return true;
}


bool USteamFriendsSubsystem::GetFriendMessage(
	const FSteamId SteamIdFriend, const int32 MessageID, FChatMessage& Message, const int32 MaxExpectedLength
) {
	const FTempString TempString(MaxExpectedLength);
	EChatEntryType ChatEntryType;
	
	const int32 Bytes = SteamFriends()->GetFriendMessage(
		SteamIdFriend.GetCSteamID(),
		MessageID,
		TempString.Start(),
		MaxExpectedLength,
		&ChatEntryType
	);

	if (Bytes <= 0)
	{
		return false;
	}

	Message.Message = TempString.ToString();
	Message.MessageType = StaticCast<ESteamChatEntryType>(ChatEntryType);

	return true;
}


FString USteamFriendsSubsystem::GetFriendPersonaName(const FSteamId SteamIdFriend)
{
	return SteamFriends()->GetFriendPersonaName(SteamIdFriend.GetCSteamID());
}


FString USteamFriendsSubsystem::GetFriendPersonaNameHistory(const FSteamId SteamIdFriend, const int32 PersonaName)
{
	return SteamFriends()->GetFriendPersonaNameHistory(SteamIdFriend.GetCSteamID(), PersonaName);
}


ESteamPersonaState USteamFriendsSubsystem::GetFriendPersonaState(const FSteamId SteamIdFriend)
{
	const EPersonaState State = SteamFriends()->GetFriendPersonaState(SteamIdFriend.GetCSteamID());
	return StaticCast<ESteamPersonaState>(State);
}


ESteamFriendRelationship USteamFriendsSubsystem::GetFriendRelationship(const FSteamId SteamIdFriend)
{
	const EFriendRelationship Relationship = SteamFriends()->GetFriendRelationship(SteamIdFriend.GetCSteamID());
	return StaticCast<ESteamFriendRelationship>(Relationship);
}


FString USteamFriendsSubsystem::GetFriendRichPresence(const FSteamId SteamIdFriend, const FString& Key)
{
	return SteamFriends()->GetFriendRichPresence(SteamIdFriend.GetCSteamID(), TCHAR_TO_UTF8(*Key));
}


FString USteamFriendsSubsystem::GetFriendRichPresenceKeyByIndex(const FSteamId SteamIdFriend, const int32 KeyIndex)
{
	return SteamFriends()->GetFriendRichPresenceKeyByIndex(SteamIdFriend.GetCSteamID(), KeyIndex);
}


int32 USteamFriendsSubsystem::GetFriendRichPresenceKeyCount(const FSteamId SteamIdFriend)
{
	return SteamFriends()->GetFriendRichPresenceKeyCount(SteamIdFriend.GetCSteamID());
}


int32 USteamFriendsSubsystem::GetFriendsGroupCount()
{
	return SteamFriends()->GetFriendsGroupCount();
}


FFriendsGroupId USteamFriendsSubsystem::GetFriendsGroupIDByIndex(const int32 FriendsGroupIndex)
{
	return SteamFriends()->GetFriendsGroupIDByIndex(FriendsGroupIndex);
}


int32 USteamFriendsSubsystem::GetFriendsGroupMembersCount(const FFriendsGroupId FriendsGroupId)
{
	return SteamFriends()->GetFriendsGroupMembersCount(FriendsGroupId.GetId());
}


void USteamFriendsSubsystem::GetFriendsGroupMembersList(
	const FFriendsGroupId FriendsGroupId, TArray<FSteamId>& SteamIdMembers, const int32 MembersCount
) {
	TArray<CSteamID> Members;

	Members.Reserve(MembersCount);
	SteamIdMembers.Reserve(MembersCount);

	SteamFriends()->GetFriendsGroupMembersList(FriendsGroupId.GetId(), Members.GetData(), MembersCount);

	for (const auto& Member : Members)
	{
		if (!Member.IsValid())
		{
			// As soon as one is invalid, return with all the already validated
			return;
		}

		SteamIdMembers.Add(Member);
	}
}


FString USteamFriendsSubsystem::GetFriendsGroupName(const FFriendsGroupId FriendsGroupId)
{
	return SteamFriends()->GetFriendsGroupName(FriendsGroupId.GetId());
}


int32 USteamFriendsSubsystem::GetFriendSteamLevel(FSteamId SteamIdFriend)
{
	return SteamFriends()->GetFriendSteamLevel(SteamIdFriend.GetCSteamID());
}


int32 USteamFriendsSubsystem::GetLargeFriendAvatar(const FSteamId SteamIdFriend)
{
	return SteamFriends()->GetLargeFriendAvatar(SteamIdFriend.GetCSteamID());
}


int32 USteamFriendsSubsystem::GetMediumFriendAvatar(const FSteamId SteamIdFriend)
{
	return SteamFriends()->GetMediumFriendAvatar(SteamIdFriend.GetCSteamID());
}


FString USteamFriendsSubsystem::GetPersonaName()
{
	return SteamFriends()->GetPersonaName();
}


ESteamPersonaState USteamFriendsSubsystem::GetPersonaState()
{
	const EPersonaState State = SteamFriends()->GetPersonaState();
	return StaticCast<ESteamPersonaState>(State);
}


FString USteamFriendsSubsystem::GetPlayerNickname(FSteamId SteamIdPlayer)
{
	return SteamFriends()->GetPlayerNickname(SteamIdPlayer.GetCSteamID());
}


int32 USteamFriendsSubsystem::GetSmallFriendAvatar(const FSteamId SteamIdFriend)
{
	return SteamFriends()->GetSmallFriendAvatar(SteamIdFriend.GetCSteamID());
}


TSet<ESteamUserRestriction> USteamFriendsSubsystem::GetUserRestrictions()
{
	const int32 Flags = SteamFriends()->GetUserRestrictions();
	return ESteamUserRestrictionHelper::ConvertBitfieldToSteamUserRestrictions(Flags);
}


bool USteamFriendsSubsystem::HasFriend(const FSteamId SteamIdFriend, const TSet<ESteamFriendFlags>& FriendFlags)
{
	const int32 Bitfield = ESteamFriendFlagsHelper::ConvertSteamFriendFlagsSetToBitfield(FriendFlags);
	return HasFriend(SteamIdFriend, Bitfield);
}


bool USteamFriendsSubsystem::HasFriend(const FSteamId SteamIdFriend, const int32 FriendFlags)
{
	return SteamFriends()->HasFriend(SteamIdFriend.GetCSteamID(), FriendFlags);
}


bool USteamFriendsSubsystem::InviteUserToGame(const FSteamId SteamIdFriend, const FString& ConnectionString)
{
	return SteamFriends()->InviteUserToGame(SteamIdFriend.GetCSteamID(), TCHAR_TO_UTF8(*ConnectionString));
}


bool USteamFriendsSubsystem::IsClanChatAdmin(const FSteamId SteamIdClanChat, const FSteamId SteamIdUser)
{
	return SteamFriends()->IsClanChatAdmin(SteamIdClanChat.GetCSteamID(), SteamIdUser.GetCSteamID());
}


bool USteamFriendsSubsystem::IsClanPublic(const FSteamId SteamIdClan)
{
	return SteamFriends()->IsClanPublic(SteamIdClan.GetCSteamID());
}


bool USteamFriendsSubsystem::IsClanOfficialGameGroup(const FSteamId SteamIdClan)
{
	return SteamFriends()->IsClanOfficialGameGroup(SteamIdClan.GetCSteamID());
}


bool USteamFriendsSubsystem::IsClanChatWindowOpenInSteam(const FSteamId SteamIdClanChat)
{
	return SteamFriends()->IsClanChatWindowOpenInSteam(SteamIdClanChat.GetCSteamID());
}


bool USteamFriendsSubsystem::LeaveClanChatRoom(const FSteamId SteamIdClan)
{
	return SteamFriends()->LeaveClanChatRoom(SteamIdClan.GetCSteamID());
}


bool USteamFriendsSubsystem::OpenClanChatWindowInSteam(const FSteamId SteamIdClanChat)
{
	return SteamFriends()->OpenClanChatWindowInSteam(SteamIdClanChat.GetCSteamID());
}


bool USteamFriendsSubsystem::ReplyToFriendMessage(const FSteamId SteamIdFriend, const FString& Message)
{
	return SteamFriends()->ReplyToFriendMessage(SteamIdFriend.GetCSteamID(), TCHAR_TO_UTF8(*Message));
}


void USteamFriendsSubsystem::RequestFriendRichPresence(const FSteamId SteamIdFriend)
{
	return SteamFriends()->RequestFriendRichPresence(SteamIdFriend.GetCSteamID());
}


bool USteamFriendsSubsystem::RequestUserInformation(const FSteamId SteamIdUser, const bool bRequireNameOnly)
{
	return SteamFriends()->RequestUserInformation(SteamIdUser.GetCSteamID(), bRequireNameOnly);
}


bool USteamFriendsSubsystem::SendClanChatMessage(const FSteamId SteamIdClanChat, const FString& Message)
{
	return SteamFriends()->SendClanChatMessage(SteamIdClanChat.GetCSteamID(), TCHAR_TO_UTF8(*Message));
}


void USteamFriendsSubsystem::SetInGameVoiceSpeaking(const bool bSpeaking)
{
	SteamFriends()->SetInGameVoiceSpeaking(CSteamID(), bSpeaking);
}


void USteamFriendsSubsystem::SetListenForFriendsMessages(const bool bInterceptEnabled)
{
	// Because it always returns true (as based on the Steamworks API docs)
	// ignore the result and return nothign, so users are not confused and do not try to handle
	// a non-error situation
	SteamFriends()->SetListenForFriendsMessages(bInterceptEnabled);
}


void USteamFriendsSubsystem::SetPlayedWith(const FSteamId SteamIdUserPlayedWith)
{
	SteamFriends()->SetPlayedWith(SteamIdUserPlayedWith.GetCSteamID());
}


bool USteamFriendsSubsystem::SetRichPresence(const FString& Key, const FString& Value)
{
	return SteamFriends()->SetRichPresence(TCHAR_TO_UTF8(*Key), TCHAR_TO_UTF8(*Value));
}


bool USteamFriendsSubsystem::HasEquippedProfileItem(
	const FSteamId SteamId, const ESteamCommunityProfileItemType ItemType
) {
	return SteamFriends()->BHasEquippedProfileItem(
		SteamId.GetCSteamID(),
		StaticCast<ECommunityProfileItemType>(ItemType)
	);
}


FString USteamFriendsSubsystem::GetProfileItemPropertyString(
	const FSteamId SteamId, const ESteamCommunityProfileItemType ItemType, const ESteamCommunityProfileItemProperty Prop
) {
	return SteamFriends()->GetProfileItemPropertyString(
		SteamId.GetCSteamID(),
		StaticCast<ECommunityProfileItemType>(ItemType),
		StaticCast<ECommunityProfileItemProperty>(Prop)
	);
}


int64 USteamFriendsSubsystem::GetProfileItemPropertyUint(
	const FSteamId SteamId, const ESteamCommunityProfileItemType ItemType, const ESteamCommunityProfileItemProperty Prop
) {
	return SteamFriends()->GetProfileItemPropertyUint(
		SteamId.GetCSteamID(),
		ESteamCommunityProfileItemTypeHelper::ToSteamEnum(ItemType),
		ESteamCommunityProfileItemPropertyHelper::ToSteamEnum(Prop)
	);
}
