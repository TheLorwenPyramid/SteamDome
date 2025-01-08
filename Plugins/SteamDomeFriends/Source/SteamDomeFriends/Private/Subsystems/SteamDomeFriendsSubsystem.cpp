// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/SteamDomeFriendsSubsystem.h"

#include <steam/isteamfriends.h>
#include <steam/isteamutils.h>

#include "Enums/SteamFriendFlags.h"
#include "Helpers/TempString.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/ChatMessage.h"
#include "Structs/ClanActivityCounts.h"
#include "Structs/FriendGameInfo.h"


USteamDomeFriendsSubsystem* USteamDomeFriendsSubsystem::Get(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<ThisClass>();
}


void USteamDomeFriendsSubsystem::ActivateGameOverlay(const EOverlayDialogSelf OverlayDialog)
{
	SteamFriends()->ActivateGameOverlay(OverlayDialog::OverlayDialogSelfToCharPtr(OverlayDialog));
}


void USteamDomeFriendsSubsystem::ActivateGameOverlayInviteDialog(const FSteamId SteamIDLobby)
{
	SteamFriends()->ActivateGameOverlayInviteDialog(SteamIDLobby.GetCSteamID());
}


void USteamDomeFriendsSubsystem::ActivateGameOverlayToStore(const FAppId AppId, const ESteamOverlayToStoreFlag Flag)
{
	SteamFriends()->ActivateGameOverlayToStore(AppId.AppId, SteamOverlayToStoreFlag::ToSteamEnum(Flag));
}


void USteamDomeFriendsSubsystem::ActivateGameOverlayToUser(const EOverlayDialogUser OverlayDialog, const FSteamId SteamId)
{
	SteamFriends()->ActivateGameOverlayToUser(
		OverlayDialog::OverlayDialogUserToCharPtr(OverlayDialog), SteamId.GetCSteamID()
	);
}


void USteamDomeFriendsSubsystem::ActivateGameOverlayToWebPage(
	const FString& URL, const ESteamActivateGameOverlayToWebPageMode Mode
) {
	SteamFriends()->ActivateGameOverlayToWebPage(
		TCHAR_TO_UTF8(*URL), SteamActivateGameOverlayToWebPageMode::ToSteamEnum(Mode)
	);
}


void USteamDomeFriendsSubsystem::ClearRichPresence()
{
	SteamFriends()->ClearRichPresence();
}


bool USteamDomeFriendsSubsystem::CloseClanChatWindowInSteam(FSteamId SteamIdClanChat)
{
	return SteamFriends()->CloseClanChatWindowInSteam(SteamIdClanChat.GetCSteamID());
}


FSteamId USteamDomeFriendsSubsystem::GetChatMemberByIndex(FSteamId SteamIdClan, int UserIndex)
{
	return SteamFriends()->GetChatMemberByIndex(SteamIdClan.GetCSteamID(), UserIndex);
}


bool USteamDomeFriendsSubsystem::GetClanActivityCounts(FSteamId SteamIdClan, FClanActivityCounts& ClanActivityCounts)
{
	return SteamFriends()->GetClanActivityCounts(
		SteamIdClan.GetCSteamID(),
		&ClanActivityCounts.Online,
		&ClanActivityCounts.InGame,
		&ClanActivityCounts.Chatting
	);
}


bool USteamDomeFriendsSubsystem::GetClanChatMessage(
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
	ChatMessage.MessageType = SteamChatEntryType::FromSteamEnum(ChatEntry);
	SteamIdChatter = FSteamId::FromCSteamID(Chatter);

	return true;
}


int32 USteamDomeFriendsSubsystem::GetClanCount()
{
	return SteamFriends()->GetClanCount();
}


FString USteamDomeFriendsSubsystem::GetClanName(const FSteamId& SteamIdClan)
{
	return FString(UTF8_TO_TCHAR(SteamFriends()->GetClanName(SteamIdClan.GetCSteamID())));
}


FSteamId USteamDomeFriendsSubsystem::GetClanOfficerByIndex(const FSteamId SteamIdClan, const int32 Officer)
{
	return SteamFriends()->GetClanOfficerByIndex(SteamIdClan.GetCSteamID(), Officer);
}


int32 USteamDomeFriendsSubsystem::GetClanOfficerCount(const FSteamId SteamIdClan)
{
	return SteamFriends()->GetClanOfficerCount(SteamIdClan.GetCSteamID());
}


FSteamId USteamDomeFriendsSubsystem::GetClanOwner(const FSteamId SteamIdClan)
{
	return SteamFriends()->GetClanOwner(SteamIdClan.GetCSteamID());
}


FString USteamDomeFriendsSubsystem::GetClanTag(const FSteamId SteamIdClan)
{
	return FString(UTF8_TO_TCHAR(SteamFriends()->GetClanTag(SteamIdClan.GetCSteamID())));
}


FSteamId USteamDomeFriendsSubsystem::GetCoplayFriend(int32 CoplayFriendIndex)
{
	return SteamFriends()->GetCoplayFriend(CoplayFriendIndex);
}


int32 USteamDomeFriendsSubsystem::GetCoplayFriendCount()
{
	return SteamFriends()->GetCoplayFriendCount();
}


FSteamId USteamDomeFriendsSubsystem::GetFriendByIndex(const int32 FriendIndex, const TSet<ESteamFriendFlags>& FriendFlags)
{
	return GetFriendByIndex(FriendIndex, SteamFriendFlags::ConvertSteamFriendFlagsSetToBitfield(FriendFlags));
}


FSteamId USteamDomeFriendsSubsystem::GetFriendByIndex(const int32 FriendIndex, const int32 FriendFlags)
{
	return SteamFriends()->GetFriendByIndex(FriendIndex, FriendFlags);
}


FAppId USteamDomeFriendsSubsystem::GetFriendCoplayGame(FSteamId SteamIdFriend)
{
	return SteamFriends()->GetFriendCoplayGame(SteamIdFriend.GetCSteamID());
}


int32 USteamDomeFriendsSubsystem::GetFriendCoplayTime(FSteamId SteamIdFriend)
{
	return SteamFriends()->GetFriendCoplayTime(SteamIdFriend.GetCSteamID());
}


int32 USteamDomeFriendsSubsystem::GetFriendCount(const int32 FriendFlags)
{
	return SteamFriends()->GetFriendCount(FriendFlags);
}


int32 USteamDomeFriendsSubsystem::GetFriendCountFromSource(const FSteamId SteamIdSource)
{
	return SteamFriends()->GetFriendCountFromSource(SteamIdSource.GetCSteamID());
}


FSteamId USteamDomeFriendsSubsystem::GetFriendFromSourceByIndex(const FSteamId SteamIdSource, const int32 FriendIndex)
{
	return SteamFriends()->GetFriendFromSourceByIndex(SteamIdSource.GetCSteamID(), FriendIndex);
}


bool USteamDomeFriendsSubsystem::GetFriendGamePlayed(const FSteamId SteamIdFriend, FFriendGameInfo& FriendGameInfo)
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


bool USteamDomeFriendsSubsystem::GetFriendMessage(
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
	Message.MessageType = SteamChatEntryType::FromSteamEnum(ChatEntryType);

	return true;
}


FString USteamDomeFriendsSubsystem::GetFriendPersonaName(const FSteamId SteamIdFriend)
{
	return FString(UTF8_TO_TCHAR(SteamFriends()->GetFriendPersonaName(SteamIdFriend.GetCSteamID())));
}


FString USteamDomeFriendsSubsystem::GetFriendPersonaNameHistory(const FSteamId SteamIdFriend, const int32 PersonaName)
{
	return FString(UTF8_TO_TCHAR(SteamFriends()->GetFriendPersonaNameHistory(SteamIdFriend.GetCSteamID(), PersonaName)));
}


ESteamPersonaState USteamDomeFriendsSubsystem::GetFriendPersonaState(const FSteamId SteamIdFriend)
{
	const EPersonaState State = SteamFriends()->GetFriendPersonaState(SteamIdFriend.GetCSteamID());
	return SteamPersonaState::FromSteamEnum(State);
}


ESteamFriendRelationship USteamDomeFriendsSubsystem::GetFriendRelationship(const FSteamId SteamIdFriend)
{
	const EFriendRelationship Relationship = SteamFriends()->GetFriendRelationship(SteamIdFriend.GetCSteamID());
	return SteamFriendRelationship::FromSteamEnum(Relationship);
}


FString USteamDomeFriendsSubsystem::GetFriendRichPresence(const FSteamId SteamIdFriend, const FString& Key)
{
	return FString(UTF8_TO_TCHAR(SteamFriends()->GetFriendRichPresence(SteamIdFriend.GetCSteamID(), TCHAR_TO_UTF8(*Key))));
}


FString USteamDomeFriendsSubsystem::GetFriendRichPresenceKeyByIndex(const FSteamId SteamIdFriend, const int32 KeyIndex)
{
	return FString(UTF8_TO_TCHAR(SteamFriends()->GetFriendRichPresenceKeyByIndex(SteamIdFriend.GetCSteamID(), KeyIndex)));
}


int32 USteamDomeFriendsSubsystem::GetFriendRichPresenceKeyCount(const FSteamId SteamIdFriend)
{
	return SteamFriends()->GetFriendRichPresenceKeyCount(SteamIdFriend.GetCSteamID());
}


int32 USteamDomeFriendsSubsystem::GetFriendsGroupCount()
{
	return SteamFriends()->GetFriendsGroupCount();
}


FFriendsGroupId USteamDomeFriendsSubsystem::GetFriendsGroupIDByIndex(const int32 FriendsGroupIndex)
{
	return SteamFriends()->GetFriendsGroupIDByIndex(FriendsGroupIndex);
}


int32 USteamDomeFriendsSubsystem::GetFriendsGroupMembersCount(const FFriendsGroupId FriendsGroupId)
{
	return SteamFriends()->GetFriendsGroupMembersCount(FriendsGroupId.GetId());
}


void USteamDomeFriendsSubsystem::GetFriendsGroupMembersList(
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


FString USteamDomeFriendsSubsystem::GetFriendsGroupName(const FFriendsGroupId FriendsGroupId)
{
	return FString(UTF8_TO_TCHAR(SteamFriends()->GetFriendsGroupName(FriendsGroupId.GetId())));
}


int32 USteamDomeFriendsSubsystem::GetFriendSteamLevel(FSteamId SteamIdFriend)
{
	return SteamFriends()->GetFriendSteamLevel(SteamIdFriend.GetCSteamID());
}


int32 USteamDomeFriendsSubsystem::GetLargeFriendAvatar(const FSteamId SteamIdFriend)
{
	return SteamFriends()->GetLargeFriendAvatar(SteamIdFriend.GetCSteamID());
}


int32 USteamDomeFriendsSubsystem::GetMediumFriendAvatar(const FSteamId SteamIdFriend)
{
	return SteamFriends()->GetMediumFriendAvatar(SteamIdFriend.GetCSteamID());
}


FString USteamDomeFriendsSubsystem::GetPersonaName()
{
	return FString(UTF8_TO_TCHAR(SteamFriends()->GetPersonaName()));
}


ESteamPersonaState USteamDomeFriendsSubsystem::GetPersonaState()
{
	const EPersonaState State = SteamFriends()->GetPersonaState();
	return SteamPersonaState::FromSteamEnum(State);
}


FString USteamDomeFriendsSubsystem::GetPlayerNickname(FSteamId SteamIdPlayer)
{
	return FString(UTF8_TO_TCHAR(SteamFriends()->GetPlayerNickname(SteamIdPlayer.GetCSteamID())));
}


int32 USteamDomeFriendsSubsystem::GetSmallFriendAvatar(const FSteamId SteamIdFriend)
{
	return SteamFriends()->GetSmallFriendAvatar(SteamIdFriend.GetCSteamID());
}


TSet<ESteamUserRestriction> USteamDomeFriendsSubsystem::GetUserRestrictions()
{
	const int32 Flags = SteamFriends()->GetUserRestrictions();
	return SteamUserRestriction::ConvertBitfieldToSteamUserRestrictions(Flags);
}


bool USteamDomeFriendsSubsystem::HasFriend(const FSteamId SteamIdFriend, const TSet<ESteamFriendFlags>& FriendFlags)
{
	const int32 Bitfield = SteamFriendFlags::ConvertSteamFriendFlagsSetToBitfield(FriendFlags);
	return HasFriend(SteamIdFriend, Bitfield);
}


bool USteamDomeFriendsSubsystem::HasFriend(const FSteamId SteamIdFriend, const int32 FriendFlags)
{
	return SteamFriends()->HasFriend(SteamIdFriend.GetCSteamID(), FriendFlags);
}


bool USteamDomeFriendsSubsystem::InviteUserToGame(const FSteamId SteamIdFriend, const FString& ConnectionString)
{
	return SteamFriends()->InviteUserToGame(SteamIdFriend.GetCSteamID(), TCHAR_TO_UTF8(*ConnectionString));
}


bool USteamDomeFriendsSubsystem::IsClanChatAdmin(const FSteamId SteamIdClanChat, const FSteamId SteamIdUser)
{
	return SteamFriends()->IsClanChatAdmin(SteamIdClanChat.GetCSteamID(), SteamIdUser.GetCSteamID());
}


bool USteamDomeFriendsSubsystem::IsClanPublic(const FSteamId SteamIdClan)
{
	return SteamFriends()->IsClanPublic(SteamIdClan.GetCSteamID());
}


bool USteamDomeFriendsSubsystem::IsClanOfficialGameGroup(const FSteamId SteamIdClan)
{
	return SteamFriends()->IsClanOfficialGameGroup(SteamIdClan.GetCSteamID());
}


bool USteamDomeFriendsSubsystem::IsClanChatWindowOpenInSteam(const FSteamId SteamIdClanChat)
{
	return SteamFriends()->IsClanChatWindowOpenInSteam(SteamIdClanChat.GetCSteamID());
}


bool USteamDomeFriendsSubsystem::LeaveClanChatRoom(const FSteamId SteamIdClan)
{
	return SteamFriends()->LeaveClanChatRoom(SteamIdClan.GetCSteamID());
}


bool USteamDomeFriendsSubsystem::OpenClanChatWindowInSteam(const FSteamId SteamIdClanChat)
{
	return SteamFriends()->OpenClanChatWindowInSteam(SteamIdClanChat.GetCSteamID());
}


bool USteamDomeFriendsSubsystem::ReplyToFriendMessage(const FSteamId SteamIdFriend, const FString& Message)
{
	return SteamFriends()->ReplyToFriendMessage(SteamIdFriend.GetCSteamID(), TCHAR_TO_UTF8(*Message));
}


void USteamDomeFriendsSubsystem::RequestFriendRichPresence(const FSteamId SteamIdFriend)
{
	return SteamFriends()->RequestFriendRichPresence(SteamIdFriend.GetCSteamID());
}


bool USteamDomeFriendsSubsystem::RequestUserInformation(const FSteamId SteamIdUser, const bool bRequireNameOnly)
{
	return SteamFriends()->RequestUserInformation(SteamIdUser.GetCSteamID(), bRequireNameOnly);
}


bool USteamDomeFriendsSubsystem::SendClanChatMessage(const FSteamId SteamIdClanChat, const FString& Message)
{
	return SteamFriends()->SendClanChatMessage(SteamIdClanChat.GetCSteamID(), TCHAR_TO_UTF8(*Message));
}


void USteamDomeFriendsSubsystem::SetInGameVoiceSpeaking(const bool bSpeaking)
{
	SteamFriends()->SetInGameVoiceSpeaking(CSteamID(), bSpeaking);
}


void USteamDomeFriendsSubsystem::SetListenForFriendsMessages(const bool bInterceptEnabled)
{
	// Because it always returns true (as based on the Steamworks API docs)
	// ignore the result and return nothign, so users are not confused and do not try to handle
	// a non-error situation
	SteamFriends()->SetListenForFriendsMessages(bInterceptEnabled);
}


void USteamDomeFriendsSubsystem::SetPlayedWith(const FSteamId SteamIdUserPlayedWith)
{
	SteamFriends()->SetPlayedWith(SteamIdUserPlayedWith.GetCSteamID());
}


bool USteamDomeFriendsSubsystem::SetRichPresence(const FString& Key, const FString& Value)
{
	return SteamFriends()->SetRichPresence(TCHAR_TO_UTF8(*Key), TCHAR_TO_UTF8(*Value));
}


bool USteamDomeFriendsSubsystem::HasEquippedProfileItem(
	const FSteamId SteamId, const ESteamCommunityProfileItemType ItemType
) {
	return SteamFriends()->BHasEquippedProfileItem(
		SteamId.GetCSteamID(),
		SteamCommunityProfileItemType::ToSteamEnum(ItemType)
	);
}


FString USteamDomeFriendsSubsystem::GetProfileItemPropertyString(
	const FSteamId SteamId, const ESteamCommunityProfileItemType ItemType, const ESteamCommunityProfileItemProperty Prop
) {
	return FString(UTF8_TO_TCHAR(SteamFriends()->GetProfileItemPropertyString(
		SteamId.GetCSteamID(),
		SteamCommunityProfileItemType::ToSteamEnum(ItemType),
		SteamCommunityProfileItemProperty::ToSteamEnum(Prop)
	)));
}


int64 USteamDomeFriendsSubsystem::GetProfileItemPropertyUint(
	const FSteamId SteamId, const ESteamCommunityProfileItemType ItemType, const ESteamCommunityProfileItemProperty Prop
) {
	return SteamFriends()->GetProfileItemPropertyUint(
		SteamId.GetCSteamID(),
		SteamCommunityProfileItemType::ToSteamEnum(ItemType),
		SteamCommunityProfileItemProperty::ToSteamEnum(Prop)
	);
}


void USteamDomeFriendsSubsystem::OnAvatarImageLoadedCallback(AvatarImageLoaded_t* AvatarImageLoaded)
{
	OnAvatarImageLoaded.Broadcast(
		FSteamId(AvatarImageLoaded->m_steamID),
		AvatarImageLoaded->m_iImage,
		AvatarImageLoaded->m_iWide,
		AvatarImageLoaded->m_iTall
	);
}


void USteamDomeFriendsSubsystem::OnPersonaStateChangeCallback(PersonaStateChange_t* PersonaStateChange)
{
	OnPersonaStateChange.Broadcast(FSteamId(PersonaStateChange->m_ulSteamID), PersonaStateChange->m_nChangeFlags);
}
