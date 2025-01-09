// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/AppId.h"
#include "Structs/SteamId.h"
#include "Enums/OverlayDialog.h"
#include "Enums/SteamActivateGameOverlayToWebPageMode.h"
#include "Enums/SteamCommunityProfileItemProperty.h"
#include "Enums/SteamCommunityProfileItemType.h"
#include "Enums/SteamFriendFlags.h"
#include "Enums/SteamFriendRelationship.h"
#include "Enums/SteamOverlayToStoreFlag.h"
#include "Enums/SteamPersonaState.h"
#include "Enums/SteamUserRestrictions.h"
#include "Structs/FriendsGroupId.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SteamDomeFriendsSubsystem.generated.h"


struct FFriendGameInfo;
struct FChatMessage;
struct FClanActivityCounts;


DECLARE_MULTICAST_DELEGATE_TwoParams(
	FOnPersonaStateChangeSignature,
	const FSteamId /* SteamId */,
	const int32 /* ChangeFlags */
);


DECLARE_MULTICAST_DELEGATE_FourParams(
	FOnAvatarImageLoadedSignature,
	const FSteamId /* SteamId */,
	const int32 /* PictureIndex */,
	const int32 /* PictureWidth */,
	const int32 /* PictureHeight */
);

/**
 * 
 */
UCLASS()
class STEAMDOMEFRIENDS_API USteamDomeFriendsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	/**
	 * Called when a large avatar is loaded if you have tried requesting it when it was unavailable.
	 * 
	 * Not exposed directly to blueprints.
	 * Functionality to execute the Avatar loading in Blueprints in done via the GetUserAvatar async task.
	 */
	FOnPersonaStateChangeSignature OnPersonaStateChange;

	FOnAvatarImageLoadedSignature OnAvatarImageLoaded;

	static USteamDomeFriendsSubsystem* Get(const UObject* WorldContextObject);
	
	/**
	 * Activates the Steam Overlay to a specific dialog.
	 *
	 * This is equivalent to calling ActivateGameOverlayToUser with SteamId set to ISteamUser::GetSteamID.
	 * 
	 * @param OverlayDialog The dialog to open
	 */
	UFUNCTION(BlueprintCallable)
	static void ActivateGameOverlay(const EOverlayDialogSelf OverlayDialog);

	/**
	 * Activates the Steam Overlay to open the invite dialog. Invitations sent from this dialog will be for the provided lobby.
	 * 
	 * @param SteamIDLobby The Steam ID of the lobby that selected users will be invited to. 
	 */
	UFUNCTION(BlueprintCallable)
	static void ActivateGameOverlayInviteDialog(const FSteamId SteamIDLobby);

	/**
	 * Activates the Steam Overlay to the Steam store page for the provided app.
	 *
	 * Using AppIdInvalid (the default for non-initialized FAppId) brings the user to the front page of the Steam store.
	 * 
	 * @param AppId The app ID to show the store page of.
	 * @param Flag Flags to modify the behavior when the page opens.
	 */
	UFUNCTION(BlueprintCallable)
	static void ActivateGameOverlayToStore(const FAppId AppId, const ESteamOverlayToStoreFlag Flag);

	/**
	 * Activates Steam Overlay to a specific dialog.
	 *
	 * Valid OverlayDialog options are:
	 * - "SteamId": Opens the overlay web browser to the specified user or groups profile.
	 * - chat: Opens a chat window to the specified user, or joins the group chat.
	 * - JoinTrade: Opens a window to a Steam Trading session that was started with the ISteamEconomy/StartTrade Web API.
	 * - Stats: Opens the overlay web browser to the specified user's stats.
	 * - Achievements: Opens the overlay web browser to the specified user's achievements.
	 * - FriendAdd: Opens the overlay in minimal mode prompting the user to add the target user as a friend.
	 * - FriendRemove: Opens the overlay in minimal mode prompting the user to remove the target friend.
	 * - FriendRequestAccept: Opens the overlay in minimal mode prompting the user to accept an incoming friend invite.
	 * - FriendRequestIgnore: Opens the overlay in minimal mode prompting the user to ignore an incoming friend invite.
	 * 
	 * @param OverlayDialog The dialog to open.
	 * @param SteamId The Steam ID of the context to open this dialog to.
	 */
	UFUNCTION(BlueprintCallable)
	static void ActivateGameOverlayToUser(const EOverlayDialogUser OverlayDialog, const FSteamId SteamId);

	/**
	 * Activates Steam Overlay web browser directly to the specified URL.
	 * 
	 * @param URL The webpage to open. (A fully qualified address with the protocol is required, e.g. "http://www.steampowered.com")
	 * @param Mode Mode for the web page. Defaults to Default
	 */
	UFUNCTION(BlueprintCallable)
	static void ActivateGameOverlayToWebPage(const FString& URL, const ESteamActivateGameOverlayToWebPageMode Mode = ESteamActivateGameOverlayToWebPageMode::Default);

	/**
	 * Clears all of the current user's Rich Presence key/values.
	 */
	UFUNCTION(BlueprintCallable)
	static void ClearRichPresence();

	/**
	 * Closes the specified Steam group chat room in the Steam UI.
	 * 
	 * @param SteamIdClanChat The SteamId of the Steam group chat room to close.
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	static bool CloseClanChatWindowInSteam(const FSteamId SteamIdClanChat);

	/** TODO: Async method
	SteamAPICall_t DownloadClanActivityCounts(TArray<FSteamId> SteamIDClans);
	*/

	/** TODO: Async method
	SteamAPICall_t EnumerateFollowingList( uint32 unStartIndex );
	*/

	/**
	 * Gets the Steam ID at the given index in a Steam group chat.
	 *
	 * @param SteamIdClan This MUST be the same source used in the previous call to GetClanChatMemberCount!
	 * @param UserIndex An index between 0 and GetClanChatMemberCount.
	 */
	UFUNCTION(BlueprintCallable)
	static FSteamId GetChatMemberByIndex(const FSteamId SteamIdClan, const int32 UserIndex);

	/**
	 * Gets the most recent information we have about what the users in a Steam Group are doing.
	 *
	 * This can only retrieve data that the local client knows about.
	 * To refresh the data or get data from a group other than one that the current user is a member
	 * of you must call DownloadClanActivityCounts.
	 * 
	 * @param SteamIdClan The Steam group to get the activity of.
	 * @param ClanActivityCounts Clan counts data.
	 * @return true if the data was successfully returned.
	 *		   false if the provided Steam ID is invalid or the local client does not have info about the
	 *		   Steam group and sets all the other parameters to 0.
	 */
	UFUNCTION(BlueprintCallable)
	static bool GetClanActivityCounts(const FSteamId SteamIdClan, FClanActivityCounts& ClanActivityCounts);

	/**
	 * This API is deprecated.
	 * 
	 * 
	 * Gets the Steam group's Steam ID at the given index.
	 *
	 * @note NOTE: You must call GetClanCount before calling this.
	 * @note SteamDome NOTE: Although this API is deprecated, I don't see another way to get a clan's SteamId.
	 *		 So this method will have to do.
	 * 
	 * @param ClanIndex An index between 0 and GetClanCount.
	 * @return Invalid indices return an invalid SteamId.
	 */
	UFUNCTION(BlueprintCallable)
	static FSteamId GetClanByIndex(const int32 ClanIndex);

	/**
	 * This API is deprecated.
	 *
	 * Get the number of users in a Steam group chat.
	 *
	 * NOTE: Large steam groups cannot be iterated by the local user.
	 * 
	 * NOTE: The current user must be in a lobby to retrieve the Steam IDs of other users in that lobby.
	 *
	 * This is used for iteration, after calling this then GetChatMemberByIndex can be used to get the Steam ID of each person in the chat.
	 * 
	 * @param SteamIdClan The Steam group to get the chat count of.
	 * @return 0 if the Steam ID provided is invalid or if the local user doesn't have the data available.
	 */
	// UFUNCTION(meta=(DeprecatedFunction))
	// static int GetClanChatMemberCount(FSteamId SteamIdClan);

	/**
	 * TODO: Review MessageIndex event
	 * Gets the data from a Steam group chat room message.
	 *
	 * This should only ever be called in response to a GameConnectedClanChatMsg_t callback.
	 *
	 * @param SteamIdClanChat The Steam ID of the Steam group chat room.
	 * @param MessageIndex The index of the message. This should be the MessageIndex field of GameConnectedClanChatMsg_t.
	 * @param ChatMessage ChatMessage that contains the message string and the ChatEntryType.
	 * @param SteamIdChatter Returns the Steam ID of the user that sent the message.
	 * @param MaxMessageLength Memory to reserve for the chat message string. (Should be big enough to hold 2048 UTF-8 characters. So 8192 bytes + 1 for '\0')
	 * @return false if the current user is not in the specified Steam group chat room or if the index provided in MessageIndex is invalid.
	 */
	UFUNCTION(BlueprintCallable)
	static bool GetClanChatMessage(
		const FSteamId SteamIdClanChat,
		const int MessageIndex,
		FChatMessage& ChatMessage,
		FSteamId& SteamIdChatter,
		const int32 MaxMessageLength = 8193 /* 8192 + 1 */
	);

	/**
	 * Gets the number of Steam groups that the current user is a member of.
	 *
	 * This is used for iteration, after calling this then GetClanByIndex can be used to get the Steam ID of each Steam group.
	 * 
	 * @return The number of Steam groups that the user is a member of.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetClanCount();

	/**
	 * Gets the display name for the specified Steam group; if the local client knows about it.
	 * 
	 * @param SteamIdClan The Steam group to get the name of.
	 * @return The Steam group's name in UTF-8 format. Returns an empty string ("") if the provided Steam ID is invalid or the user does not know about the group.
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetClanName(const FSteamId& SteamIdClan);

	/**
	 * Gets the Steam ID of the officer at the given index in a Steam group.
	 *
	 * @note NOTE: You must call GetClanOfficerCount before calling this.
	 * 
	 * @param SteamIdClan This must be the same steam group used in the previous call to GetClanOfficerCount!
	 * @param Officer An index between 0 and GetClanOfficerCount.
	 * @return Gets the Steam ID of the officer at the given index in a Steam group.
	 */
	UFUNCTION(BlueprintCallable)
	static FSteamId GetClanOfficerByIndex(const FSteamId SteamIdClan, const int32 Officer);

	/**
	 * Gets the number of officers (administrators and moderators) in a specified Steam group.
	 *
	 * This also includes the owner of the Steam group.
	 *
	 * This is used for iteration, after calling this then GetClanOfficerByIndex can be used to get the Steam ID of each officer.
	 *
	 * @note NOTE: You must call RequestClanOfficerList before this to get the required data!
	 * 
	 * @param SteamIdClan The Steam group to get the officer count of.
	 * @return The number of officers in the Steam group. Returns 0 if steamIDClan is invalid or if RequestClanOfficerList has not been called for it.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetClanOfficerCount(const FSteamId SteamIdClan);

	/**
	 * Gets the owner of a Steam Group.
	 *
	 * @note NOTE: You must call RequestClanOfficerList before this to get the required data!
	 * 
	 * @param SteamIdClan The Steam ID of the Steam group to get the owner for.
	 * @return Returns SteamIdNil if SteamIdClan is invalid or if RequestClanOfficerList has not been called for it.
	 */
	UFUNCTION(BlueprintCallable)
	static FSteamId GetClanOwner(const FSteamId SteamIdClan);

	/**
	 * Gets the unique tag (abbreviation) for the specified Steam group; If the local client knows about it.
	 *
	 * The Steam group abbreviation is a unique way for people to identify the group and is limited to 12 characters.
	 * In some games this will appear next to the name of group members.
	 * 
	 * @param SteamIdClan The Steam group to get the tag of.
	 * @return The Steam groups tag. Returns an empty string ("") if the provided Steam ID is invalid or the user does not know about the group.
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetClanTag(const FSteamId SteamIdClan);

	/**
	 * Gets the Steam ID of the recently played with user at the given index.
	 * 
	 * @note NOTE: You must call GetCoplayFriendCount before calling this.
	 * 
	 * @param CoplayFriendIndex An index between 0 and GetCoplayFriendCount.
	 * @return The SteamId of the friend. Invalid indices return an invalid SteamId.
	 */
	UFUNCTION(BlueprintCallable)
	static FSteamId GetCoplayFriend(const int32 CoplayFriendIndex);

	// TODO: EXTRA Combine GetCoplayFriend and GetCoplayFriendCount into a single method for ease of use.

	/**
	 * Gets the number of players that the current user has recently played with, across all games.
	 *
	 * This is used for iteration, after calling this then GetCoplayFriend can be used to get the Steam ID of each player.
	 *
	 * These players are have been set with previous calls to SetPlayedWith.
	 * 
	 * @return The number of users that the current user has recently played with.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetCoplayFriendCount();

	/**
	 * Gets the Steam ID of the user at the given index.
	 *
	 * @note NOTE: You must call GetFriendCount before calling this.
	 * 
	 * @param FriendIndex An index between 0 and GetFriendCount.
	 * @param FriendFlags A combined union (binary "or") of ESteamFriendFlags. This must be the same value as used in the previous call to GetFriendCount.
	 * @return Invalid indices return an invalid SteamId.
	 */
	UFUNCTION(BlueprintCallable)
	static FSteamId GetFriendByIndex(const int32 FriendIndex, const TSet<ESteamFriendFlags>& FriendFlags);

	/**
	 * C++ only version. Gets the Steam ID of the user at the given index.
	 * 
	 * @note Prefer this one over the other one, as this one should be easier to use in directly in C++.
	 * @note NOTE: You must call GetFriendCount before calling this.
	 * 
	 * @param FriendIndex An index between 0 and GetFriendCount.
	 * @param FriendFlags A combined union (binary "or") of ESteamFriendFlags. This must be the same value as used in the previous call to GetFriendCount.
	 * @return Invalid indices return an invalid SteamId.
	 */
	static FSteamId GetFriendByIndex(const int32 FriendIndex, const int32 FriendFlags);

	/**
	 * Gets the app ID of the game that user played with someone on their recently-played-with list.
	 * 
	 * @param SteamIdFriend The Steam ID of the user on the recently-played-with list to get the game played.
	 * @return Steam IDs not in the recently-played-with list return an invalid AppId.
	 */
	UFUNCTION(BlueprintCallable)
	FAppId GetFriendCoplayGame(const FSteamId SteamIdFriend);

	/**
	 * Gets the timestamp of when the user played with someone on their recently-played-with list.
	 * 
	 * @param SteamIdFriend The Steam ID of the user on the recently-played-with list to get the timestamp for.
	 * @return The time is provided in Unix epoch format (seconds since Jan 1st 1970).
	 *		   Steam IDs not in the recently-played-with list return 0.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetFriendCoplayTime(const FSteamId SteamIdFriend);

	/**
	 * Gets the number of users the client knows about who meet a specified criteria.
	 * (Friends, blocked, users on the same server, etc)
	 *
	 * This can be used to iterate over all of the users by calling GetFriendByIndex to get the Steam IDs of each user.
	 *
	 * @note NOTE: Returns -1 if the current user is not logged on.
	 * 
	 * @param FriendFlags A combined union (binary "or") of one or more EFriendFlags.
	 * @return The number of users that meet the specified criteria.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetFriendCount(UPARAM(meta=(Bitmask, BitmaskEnum=EFriendFlags)) const int32 FriendFlags);

	/**
	 * Get the number of users in a source (Steam group, chat room, lobby, or game server).
	 *
	 * This is used for iteration, after calling this then GetFriendFromSourceByIndex
	 * can be used to get the Steam ID of each person in the source.
	 *
	 * @note NOTE: Large Steam groups cannot be iterated by the local user.
	 * @note NOTE: If you're getting the number of lobby members then
	 * you should use ISteamMatchmaking::GetNumLobbyMembers instead.
	 * 
	 * @param SteamIdSource The Steam group, chat room, lobby or game server to get the user count of.
	 * @return 0 if the Steam ID provided is invalid or if the local user doesn't have the data available.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetFriendCountFromSource(const FSteamId SteamIdSource);

	/**
	 * Gets the Steam ID at the given index from a source (Steam group, chat room, lobby, or game server).
	 *
	 * @note NOTE: You must call GetFriendCountFromSource before calling this.
	 * 
	 * @param SteamIdSource This MUST be the same source used in the previous call to GetFriendCountFromSource!
	 * @param FriendIndex An index between 0 and GetFriendCountFromSource.
	 * @return Invalid indices return an invalid SteamId.
	 */
	UFUNCTION(BlueprintCallable)
	FSteamId GetFriendFromSourceByIndex(const FSteamId SteamIdSource, const int32 FriendIndex);

	/**
	 * Checks if the specified friend is in a game, and gets info about the game if they are.
	 * 
	 * @param SteamIdFriend The Steam ID of the other user.
	 * @param FriendGameInfo Details of the user game if the user is in a game.
	 * @return true if the user is a friend and is in a game; otherwise, false.
	 */
	UFUNCTION(BlueprintCallable)
	static bool GetFriendGamePlayed(const FSteamId SteamIdFriend, FFriendGameInfo& FriendGameInfo);

	/**
	 * TODO: Check GameConnectedFriendChatMsg_t comment.
	 * Gets the data from a Steam friends message.
	 *
	 * This should only ever be called in response to a GameConnectedFriendChatMsg_t callback.
	 * 
	 * @param SteamIdFriend The Steam ID of the friend that sent this message.
	 * @param MessageID The index of the message. This should be the MessageID field of GameConnectedFriendChatMsg_t.
	 * @param Message Message string.
	 * @param MaxExpectedLength Maximum expected size of the message in bytes.
	 * @return false if the current user is chat restricted, if the provided Steam ID is not a friend,
	 *		   or if the index provided in MessageID is invalid.
	 */
	UFUNCTION(BlueprintCallable)
	static bool GetFriendMessage(const FSteamId SteamIdFriend, const int32 MessageID, FChatMessage& Message, const int32 MaxExpectedLength = 8193 /* 8192 + 1*/);

	/**
	 * Gets the specified user's persona (display) name.
	 *
	 * This will only be known to the current user if the other user is in their friends list, on the same game server,
	 * in a chat room or lobby, or in a small Steam group with the local user.
	 *
	 * To get the persona name of the current user use GetPersonaName.
	 *
	 * @note NOTE: Upon on first joining a lobby, chat room, or game server the current user will not known the name
	 * of the other users automatically; that information will arrive asynchronously via PersonaStateChange_t callbacks.
	 * 
	 * @param SteamIdFriend The Steam ID of the other user.
	 * @return The current user's persona name.
	 *		   Returns an empty string (""), or "[unknown]" if the Steam ID is invalid or not known to the caller.
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetFriendPersonaName(const FSteamId SteamIdFriend);

	/**
	 * Gets one of the previous display names for the specified user.
	 *
	 * This only works for display names that the current user has seen on the local computer.
	 * 
	 * @param SteamIdFriend The Steam ID of the other user.
	 * @param PersonaName The index of the history to receive. 0 is their current persona name,
	 *		  1 is their most recent before they changed it, etc.
	 * @return The players old persona name at the given index.
	 *		   Returns an empty string when there are no further items in the history.
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetFriendPersonaNameHistory(const FSteamId SteamIdFriend, const int32 PersonaName);

	/**
	 * Gets the current status of the specified user.
	 *
	 * This will only be known to the current user if the other user is in their friends list,
	 * on the same game server, in a chat room or lobby, or in a small Steam group with the local user.
	 *
	 * To get the state of the current user use GetPersonaState.
	 * 
	 * @param SteamIdFriend The Steam ID of the other user.
	 * @return The friend state of the specified user. (Online, Offline, In-Game, etc)
	 */
	UFUNCTION(BlueprintCallable)
	static ESteamPersonaState GetFriendPersonaState(const FSteamId SteamIdFriend);

	/**
	 * Gets a relationship to a specified user.
	 * 
	 * @param SteamIdFriend The Steam ID of the other user.
	 * @return How the users know each other.
	 */
	UFUNCTION(BlueprintCallable)
	static ESteamFriendRelationship GetFriendRelationship(const FSteamId SteamIdFriend);

	/**
	 * Get a Rich Presence value from a specified friend.
	 * 
	 * @param SteamIdFriend The friend to get the Rich Presence value for.
	 * @param Key The Rich Presence key to request.
	 * @return Returns an empty string ("") if the specified key is not set.
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetFriendRichPresence(const FSteamId SteamIdFriend, const FString& Key);

	/**
	 * Get a Rich Presence value by its index, call GetFriendRichPresenceKeyCount to know the number of keys.
	 * 
	 * @param SteamIdFriend This should be the same user provided to the previous call to GetFriendRichPresenceKeyCount!
	 * @param KeyIndex An index between 0 and GetFriendRichPresenceKeyCount.
	 * @return Returns an empty string ("") if the index is invalid or the specified user has no Rich Presence data available.
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetFriendRichPresenceKeyByIndex(const FSteamId SteamIdFriend, const int32 KeyIndex);

	/**
	 * Gets the number of Rich Presence keys that are set on the specified user.
	 *
	 * This is used for iteration, after calling this then GetFriendRichPresenceKeyByIndex to get the rich presence keys.
	 *
	 * This is typically only ever used for debugging purposes.
	 * 
	 * @param SteamIdFriend The Steam ID of the user to get the Rich Presence Key Count of.
	 * @return Returns 0 if there is no Rich Presence information for the specified user.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetFriendRichPresenceKeyCount(const FSteamId SteamIdFriend);

	/**
	 * Gets the number of friends groups (tags) the user has created.
	 *
	 * This is used for iteration, after calling this then GetFriendsGroupIDByIndex can be used to get the ID of each friend group.
	 *
	 * This is not to be confused with Steam groups. Those can be obtained with GetClanCount.
	 * 
	 * @return The number of friends groups the current user has.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetFriendsGroupCount();

	/**
	 * Gets the friends group ID for the given index.
	 *
	 * @note NOTE: You must call GetFriendsGroupCount before calling this.
	 * 
	 * @param FriendsGroupIndex An index between 0 and GetFriendsGroupCount.
	 * @return Invalid indices return an invalid FriendsGroupId.
	 */
	UFUNCTION(BlueprintCallable)
	static FFriendsGroupId GetFriendsGroupIDByIndex(const int32 FriendsGroupIndex);

	/**
	 * Gets the number of friends in a given friends group.
	 *
	 * This should be called before getting the list of friends with GetFriendsGroupMembersList.
	 * 
	 * @param FriendsGroupId The friends group ID to get the number of friends in.
	 * @return The number of friends in the specified friends group.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetFriendsGroupMembersCount(const FFriendsGroupId FriendsGroupId);

	/**
	 * Gets the number of friends in the given friends group.
	 *
	 * If fewer friends exist than requested those positions' Steam IDs will be invalid.
	 *
	 * You must call GetFriendsGroupMembersCount before calling this to set up the MembersCount array with an appropriate size!
	 * 
	 * @param FriendsGroupId The friends group ID to get the members list of.
	 * @param SteamIdMembers Returns the Steam IDs of the friends by setting them in this array.
	 * @param MembersCount This should match the number of elements allocated pOutSteamIDMembers and the value
	 *		  returned by GetFriendsGroupMembersCount.
	 */
	UFUNCTION(BlueprintCallable)
	static void GetFriendsGroupMembersList(const FFriendsGroupId FriendsGroupId, TArray<FSteamId>& SteamIdMembers, const int32 MembersCount);

	/**
	 * Gets the name for the given friends group.
	 * 
	 * @param FriendsGroupId The friends group ID to get the name of.
	 * @return The friend groups name in UTF-8 format. Returns NULL if the group ID is invalid.
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetFriendsGroupName(const FFriendsGroupId FriendsGroupId);

	/**
	 * Gets the Steam level of the specified user.
	 *
	 * You can use the local users Steam ID (ISteamUser::GetSteamID) to get their level.
	 * 
	 * @param SteamIdFriend The Steam level if it's available.
	 * @return If the Steam level is not immediately available for the specified user then this returns 0
	 *		   and queues it to be downloaded from the Steam servers. When it gets downloaded a PersonaStateChange_t
	 *		   callback will be posted with m_nChangeFlags including k_EPersonaChangeSteamLevel.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetFriendSteamLevel(const FSteamId SteamIdFriend);

	/**
	 * Gets a handle to the large (128*128px) avatar for the specified user.
	 *
	 * You can pass in ISteamUser::GetSteamID to get the current user's avatar.
	 *
	 * @note NOTE: This only works for users that the local user knows about. They will automatically know about
	 *		 their friends, people on leaderboards they've requested, or people in the same source as them
	 *		 (Steam group, chat room, lobby, or game server). If they don't know about them then you must call
	 *		 RequestUserInformation to cache the avatar locally.
	 * 
	 * @param SteamIdFriend SteamId for the friend.
	 * @return A Steam image handle which is used with ISteamUtils::GetImageSize and ISteamUtils::GetImageRGBA.
	 *		   Returns 0 if no avatar is set for the user.
	 *		   Returns -1 if the avatar image data has not been loaded yet and requests that it gets download.
	 *		   In this case wait for a AvatarImageLoaded_t callback and then call this again.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetLargeFriendAvatar(const FSteamId SteamIdFriend);

	/**
	 * Gets a handle to the medium (64*64px) avatar for the specified user.
	 *
	 * You can pass in ISteamUser::GetSteamID to get the current user's avatar.
	 *
	 * @note NOTE: This only works for users that the local user knows about. They will automatically know about
	 *		 their friends, people on leaderboards they've requested, or people in the same source as them
	 *		 (Steam group, chat room, lobby, or game server). If they don't know about them then you must call
	 *		 RequestUserInformation to cache the avatar locally.
	 *		 
	 * @param SteamIdFriend SteamId for the friend.
	 * @return A Steam image handle which is used with ISteamUtils::GetImageSize and ISteamUtils::GetImageRGBA.
	 *		   Returns 0 if no avatar is set for the user.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetMediumFriendAvatar(const FSteamId SteamIdFriend);

	/**
	 * Gets the current user's persona (display) name.
	 *
	 * This is the same name that is displayed the user's community profile page.
	 *
	 * To get the persona name of other users use GetFriendPersonaName.
	 * 
	 * @return The current user's persona name.
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetPersonaName();

	/**
	 * Gets the friend status of the current user.
	 *
	 * To get the state of other users use GetFriendPersonaState.
	 * 
	 * @return The friend state of the current user. (Online, Offline, In-Game, etc)
	 */
	UFUNCTION(BlueprintCallable)
	static ESteamPersonaState GetPersonaState();

	/**
	 * Gets the nickname that the current user has set for the specified user.
	 * 
	 * @param SteamIdPlayer The Steam ID of the user.
	 * @return Empty if the no nickname has been set for that user.
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetPlayerNickname(const FSteamId SteamIdPlayer);

	/**
	 * Gets a handle to the small (32*32px) avatar for the specified user.
	 *
	 * You can pass in ISteamUser::GetSteamID to get the current user's avatar.
	 *
	 * @note NOTE: This only works for users that the local user knows about. They will automatically know about their
	 *		 friends, people on leaderboards they've requested, or people in the same source as them
	 *		 (Steam group, chat room, lobby, or game server). If they don't know about them then you must call
	 *		 RequestUserInformation to cache the avatar locally.
	 * 
	 * @param SteamIdFriend The Steam ID of the user.
	 * @return A Steam image handle which is used with ISteamUtils::GetImageSize and ISteamUtils::GetImageRGBA.
	 *		   Returns 0 if no avatar is set for the user.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetSmallFriendAvatar(const FSteamId SteamIdFriend);

	/**
	 * TODO: Needs heavy testing
	 * Checks if current user is chat restricted.
	 *
	 * If they are restricted, then they can't send or receive any text/voice chat messages, can't see custom avatars.
	 * A chat restricted user can't add friends or join any groups.
	 * Restricted users can still be online and send/receive game invites.
	 * 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	static TSet<ESteamUserRestriction> GetUserRestrictions();

	/**
	 * Checks if the user meets the specified criteria. (Friends, blocked, users on the same server, etc)
	 * 
	 * @param SteamIdFriend The Steam user to check the friend status of.
	 * @param FriendFlags A set of Flags to check against.
	 * @return true if the specified user meets any of the criteria specified in FriendFlags; otherwise, false.
	 */
	UFUNCTION(BlueprintCallable)
	static bool HasFriend(const FSteamId SteamIdFriend, const TSet<ESteamFriendFlags>& FriendFlags);
	static bool HasFriend(const FSteamId SteamIdFriend, const int32 FriendFlags);

	/**
	 * Invites a friend or clan member to the current game using a special invite string.
	 *
	 * If the target user accepts the invite then the ConnectString gets added to the command-line
	 * when launching the game.
	 * If the game is already running for that user, then they will receive a
	 * GameRichPresenceJoinRequested callback with the connect string.
	 * 
	 * @param SteamIdFriend The Steam ID of the friend to invite.
	 * @param ConnectionString A string that lets the friend know how to join the game (I.E. the game server IP).
	 *		  This can not be longer than specified in k_cchMaxRichPresenceValueLength.
	 * @return true if the invite was successfully sent.
	 *		   false under the following conditions:
	 *			-  The Steam ID provided to steamIDFriend was invalid.
	 *			-  The Steam ID provided to steamIDFriend is not a friend or
	 *			   does not share the same Steam Group as the current user.
	 *			-  The value provided to ConnectString was too long.
	 */
	UFUNCTION(BlueprintCallable)
	static bool InviteUserToGame(const FSteamId SteamIdFriend, const FString& ConnectionString);

	/**
	 * Checks if a user in the Steam group chat room is an admin.
	 * 
	 * @param SteamIdClanChat The Steam ID of the Steam group chat room.
	 * @param SteamIdUser The Steam ID of the user to check the admin status of.
	 * @return true if the specified user is an admin.
	 *		   false if the user is not an admin, if the current user is not in the chat room specified,
	 *		   or the specified user is not in the chat room.
	 */
	UFUNCTION(BlueprintCallable)
	static bool IsClanChatAdmin(const FSteamId SteamIdClanChat, const FSteamId SteamIdUser);

	/**
	 * Checks if the Steam group is public.
	 * 
	 * @param SteamIdClan The Steam ID of the Steam group.
	 * @return true if the specified group is public, false if the specified group is not public
	 */
	UFUNCTION(BlueprintCallable)
	static bool IsClanPublic(const FSteamId SteamIdClan);

	/**
	 * Checks if the Steam group is an official game group/community hub.
	 * 
	 * @param SteamIdClan The Steam ID of the Steam group.
	 * @return true if the specified group is an official game group/community hub, false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	static bool IsClanOfficialGameGroup(const FSteamId SteamIdClan);

	/**
	 * Checks if the Steam Group chat room is open in the Steam UI.
	 * 
	 * @param SteamIdClanChat The Steam ID of the Steam group chat room to check.
	 * @return true if the specified Steam group chat room is opened; otherwise, false.
	 *		   This also returns false if the specified Steam group chat room is unknown.
	 */
	UFUNCTION(BlueprintCallable)
	static bool IsClanChatWindowOpenInSteam(const FSteamId SteamIdClanChat);

	// TODO: Async method
	// UFUNCTION(BlueprintCallable)
	// static SteamAPICall_t IsFollowing( CSteamID steamID );

	/**
	 * @deprecated This API is deprecated.
	 *
	 * Checks if a specified user is in a source (Steam group, chat room, lobby, or game server).
	 * 
	 * @param SteamIdUser The user to check if they are in the source.
	 * @param SteamIdSource The source to check for the user.
	 * @return true if the local user can see that steamIDUser is a member or in steamIDSource; otherwise, false.
	 */
	// UFUNCTION(meta=(DeprecatedFunction))
	// static bool IsUserInSource(const FSteamId SteamIdUser, const FSteamId SteamIdSource);

	// TODO: Async method
	// static SteamAPICall_t JoinClanChatRoom( CSteamID steamIDClan );

	/**
	 * Leaves a Steam group chat that the user has previously entered with JoinClanChatRoom.
	 *
	 * @note Triggers a GameConnectedChatLeave callback.
	 * 
	 * @param SteamIdClan The Steam ID of the Steam group chat to leave.
	 * @return true if user is in the specified chat room, otherwise false.
	 */
	UFUNCTION(BlueprintCallable)
	static bool LeaveClanChatRoom(const FSteamId SteamIdClan);

	/**
	 * Opens the specified Steam group chat room in the Steam UI.
	 * 
	 * @param SteamIdClanChat The Steam ID of the Steam group chat room to open.
	 *
	 * @see See Also: IsClanChatWindowOpenInSteam, CloseClanChatWindowInSteam
	 * 
	 * @return true if the user successfully entered the Steam group chat room.
	 *		   false in one of the following situations:
	 *			 - The provided Steam group chat room does not exist or the user does not have access to join it.
	 *			 - The current user is currently rate limited.
	 *			 - The current user is chat restricted.
	 */
	UFUNCTION(BlueprintCallable)
	static bool OpenClanChatWindowInSteam(const FSteamId SteamIdClanChat);

	/**
	 * Sends a message to a Steam friend.
	 * 
	 * @param SteamIdFriend The Steam ID of the friend to send the message to.
	 * @param Message The UTF-8 formatted message to send.
	 * @return true if the message was successfully sent. false if the current user is rate limited or chat restricted.
	 */
	UFUNCTION(BlueprintCallable)
	static bool ReplyToFriendMessage(const FSteamId SteamIdFriend, const FString& Message);

	// TODO: Async method
	// UFUNCTION(BlueprintCallable)
	// SteamAPICall_t RequestClanOfficerList( CSteamID steamIDClan );

	/**
	 * Requests Rich Presence data from a specific user.
	 *
	 * This is used to get the Rich Presence information from a user that is not a friend of the current user,
	 * like someone in the same lobby or game server.
	 *
	 * This function is rate limited, if you call this too frequently for a particular user then it will just
	 * immediately post a callback without requesting new data from the server.
	 *
	 * @note Triggers a FriendRichPresenceUpdate callback.
	 * 
	 * @param SteamIdFriend The Steam ID of the user to request the rich presence of.
	 */
	UFUNCTION(BlueprintCallable)
	static void RequestFriendRichPresence(const FSteamId SteamIdFriend);

	/**
	 * Requests the persona name and optionally the avatar of a specified user.
	 *
	 * @note NOTE: It's a lot slower to download avatars and churns the local cache, so if you don't need avatars, don't request them.
	 * 
	 * @param SteamIdUser The user to request the information of.
	 * @param bRequireNameOnly Retrieve the Persona name only (true)? Or both the name and the avatar (false)?
	 * @return Triggers a PersonaStateChange callback.
	 *		   true means that the data has being requested, and a PersonaStateChange
	 *		   callback will be posted when it's retrieved.
	 *		   false means that we already have all the details about that user,
	 *		   and functions that require this information can be used immediately.
	 */
	UFUNCTION(BlueprintCallable)
	static bool RequestUserInformation(const FSteamId SteamIdUser, const bool bRequireNameOnly);

	/**
	 * Sends a message to a Steam group chat room.
	 * 
	 * @param SteamIdClanChat The Steam ID of the group chat to send the message to.
	 * @param Message The UTF-8 formatted message to send. This can be up to 2048 characters long.
	 * @return true if the message was successfully sent.
	 *		   false under one of the following circumstances:
	 *			- The current user is not in the specified group chat.
	 *			- The current user is not connected to Steam.
	 *			- The current user is rate limited.
	 *			- The current user is chat restricted.
	 *			- The message in pchText exceeds 2048 characters.
	 */
	UFUNCTION(BlueprintCallable)
	static bool SendClanChatMessage(const FSteamId SteamIdClanChat, const FString& Message);

	/**
	 * Let Steam know that the user is currently using voice chat in game.
	 *
	 * This will suppress the microphone for all voice communication in the Steam UI.
	 * 
	 * @param bSpeaking Did the user start speaking in game (true) or stopped speaking in game (false)?
	 */
	UFUNCTION(BlueprintCallable)
	static void SetInGameVoiceSpeaking(const bool bSpeaking);

	/**
	 * Listens for Steam friends chat messages.
	 *
	 * You can then show these chats inline in the game. For example, the chat system in Dota 2.
	 *
	 * @note Triggers a GameConnectedFriendChatMsg_t callback.
	 *
	 * After enabling this you will receive GameConnectedFriendChatMsg callbacks whenever the user
	 * receives a chat message. You can get the actual message data from this callback with GetFriendMessage.
	 * You can send messages with ReplyToFriendMessage.
	 * @param bInterceptEnabled Turn friends message interception on (true) or off (false)?
	 */
	UFUNCTION(BlueprintCallable)
	static void SetListenForFriendsMessages(const bool bInterceptEnabled);

	// TODO: Async method
	// static SteamAPICall_t SetPersonaName( const char *pchPersonaName );

	/**
	 * Mark a target user as 'played with'.
	 *
	 * NOTE: The current user must be in game with the other player for the association to work.
	 *
	 * You can view the players you have recently played with on the Steam community and in the Steam Overlay.
	 * 
	 * @param SteamIdUserPlayedWith The other user that we have played with.
	 */
	UFUNCTION(BlueprintCallable)
	static void SetPlayedWith(const FSteamId SteamIdUserPlayedWith);

	/**
	 * Sets a Rich Presence key/value for the current user that is automatically shared to all friends
	 * playing the same game.
	 *
	 * Each user can have up to 20 keys set as defined by k_cchMaxRichPresenceKeys.
	 *
	 * There are two special keys used for viewing/joining games:
	 *	- "status": A UTF-8 string that will show up in the 'view game info' dialog in the Steam friends list.
	 *	- "connect": A UTF-8 string that contains the command-line for how a friend can connect to a game.
	 *	  This enables the 'join game' button in the 'view game info' dialog, in the steam friends list right click
	 *	  menu, and on the players Steam community profile. Be sure your app implements
	 *	  ISteamApps::GetLaunchCommandLine so you can disable the popup warning when launched via a command line.
	 *
	 * There are three additional special keys used by the new Steam Chat:
	 *	- "steam_display" - Names a rich presence localization token that will be displayed in the viewing user's
	 *	  selected language in the Steam client UI. See Rich Presence Localization for more info, including a link
	 *	  to a page for testing this rich presence data. If steam_display is not set to a valid localization tag,
	 *	  then rich presence will not be displayed in the Steam client.
	 *	- "steam_player_group" - When set, indicates to the Steam client that the player is a member of a particular
	 *	  group. Players in the same group may be organized together in various places in the Steam UI.
	 *	  This string could identify a party, a server, or whatever grouping is relevant for your game.
	 *	  The string itself is not displayed to users.
	 *	- "steam_player_group_size" - When set, indicates the total number of players in the steam_player_group.
	 *	  The Steam client may use this number to display additional information about a group when all the members
	 *	  are not part of a user's friends list. (For example, "Bob, Pete, and 4 more".)
	 *
	 * You can clear all the keys for the current user with ClearRichPresence.
	 *
	 * To get rich presence keys for friends see: GetFriendRichPresence.
	 * 
	 * @param Key The rich presence 'key' to set. This can not be longer than specified in k_cchMaxRichPresenceKeyLength.
	 * @param Value The rich presence 'value' to associate with pchKey. This can not be longer than specified in k_cchMaxRichPresenceValueLength.
	 *			    If this is set to an empty string ("") or NULL then the key is removed if it's set.
	 * @return true if the rich presence was set successfully.
	 *		   false under the following conditions:
	 *			- Key was longer than k_cchMaxRichPresenceKeyLength or had a length of 0.
	 *			- Value was longer than k_cchMaxRichPresenceValueLength.
	 *			- The user has reached the maximum amount of rich presence keys as defined by k_cchMaxRichPresenceKeys.
	 */
	UFUNCTION(BlueprintCallable)
	static bool SetRichPresence(const FString& Key, const FString& Value);

	// TODO: Async method
	// static SteamAPICall_t RequestEquippedProfileItems( CSteamID steamID);

	/**
	 * After calling RequestEquippedProfileItems, you can use this function to check if the user has a type
	 * of profile item equipped or not.
	 *
	 * See Also: RequestEquippedProfileItems, GetProfileItemPropertyString, GetProfileItemPropertyUint
	 * 
	 * @param SteamId The user that you had already retrieved equipped items for
	 * @param ItemType Type of item you want to see is equipped or not
	 * @return true if the itemType is equipped for the user, false if the itemType is not equipped for the user
	 */
	UFUNCTION(BlueprintCallable)
	static bool HasEquippedProfileItem(const FSteamId SteamId,const ESteamCommunityProfileItemType ItemType);

	/**
	 * Returns a string property for a user's equipped profile item.
	 *
	 * See Also: RequestEquippedProfileItems, GetProfileItemPropertyUint
	 * 
	 * @param SteamId The user that you had already retrieved equipped items for
	 * @param ItemType Type of item you are retrieving the property for
	 * @param Prop The string property you want to retrieve
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	static FString GetProfileItemPropertyString(
		const FSteamId SteamId,
		const ESteamCommunityProfileItemType ItemType,
		const ESteamCommunityProfileItemProperty Prop
	);

	/**
	 * Returns a signed int64 (the original Steam method returns an unsigned integer) property
	 * for a user's equipped profile item.
	 *
	 * See Also: RequestEquippedProfileItems, GetProfileItemPropertyString
	 * 
	 * @param SteamId The user that you had already retrieved equipped items for
	 * @param ItemType Type of item you are retrieving the property for
	 * @param Prop The unsigned integer property you want to retrieve
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	static int64 GetProfileItemPropertyUint(
		const FSteamId SteamId,
		const ESteamCommunityProfileItemType ItemType,
		const ESteamCommunityProfileItemProperty Prop
	);

protected:

	STEAM_CALLBACK(ThisClass, OnAvatarImageLoadedCallback, AvatarImageLoaded_t);
	STEAM_CALLBACK(ThisClass, OnPersonaStateChangeCallback, PersonaStateChange_t);
};
