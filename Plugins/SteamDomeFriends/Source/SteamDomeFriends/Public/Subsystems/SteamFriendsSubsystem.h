// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/AppId.h"
#include "Structs/SteamId.h"
#include "Enums/OverlayDialog.h"
#include "Enums/SteamActivateGameOverlayToWebPageMode.h"
#include "Enums/SteamFriendFlags.h"
#include "Enums/SteamFriendRelationship.h"
#include "Enums/SteamOverlayToStoreFlag.h"
#include "Enums/SteamPersonaState.h"
#include "Enums/SteamUserRestrictions.h"
#include "Structs/FriendsGroupId.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SteamFriendsSubsystem.generated.h"


struct FFriendGameInfo;
struct FChatMessage;
struct FClanActivityCounts;
/**
 * 
 */
UCLASS()
class STEAMDOMEFRIENDS_API USteamFriendsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	/**
	 * Activates the Steam Overlay to a specific dialog.
	 *
	 * This is equivalent to calling ActivateGameOverlayToUser with steamID set to ISteamUser::GetSteamID.
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
	static bool CloseClanChatWindowInSteam(FSteamId SteamIdClanChat);

	
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
	static FSteamId GetChatMemberByIndex(FSteamId SteamIdClan, int UserIndex);

	
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
	static bool GetClanActivityCounts(FSteamId SteamIdClan, FClanActivityCounts& ClanActivityCounts);

	
	/**
	 * This API is deprecated.
	 * 
	 * Gets the Steam group's Steam ID at the given index.
	 *
	 * NOTE: You must call GetClanCount before calling this.
	 * 
	 * @param ClanIndex An index between 0 and GetClanCount.
	 * @return Invalid indices return k_steamIDNil.
	 */
	// UFUNCTION(meta=(DeprecatedFunction))
	// static FSteamId GetClanByIndex(int32 ClanIndex);

	
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
	static FSteamId GetCoplayFriend(int32 CoplayFriendIndex);

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
	FAppId GetFriendCoplayGame(FSteamId SteamIdFriend);


	/**
	 * Gets the timestamp of when the user played with someone on their recently-played-with list.
	 * 
	 * @param SteamIdFriend The Steam ID of the user on the recently-played-with list to get the timestamp for.
	 * @return The time is provided in Unix epoch format (seconds since Jan 1st 1970).
	 *		   Steam IDs not in the recently-played-with list return 0.
	 */
	UFUNCTION(BlueprintCallable)
	static int32 GetFriendCoplayTime(FSteamId SteamIdFriend);


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
	UFUNCTION()
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
	UFUNCTION()
	static ESteamPersonaState GetFriendPersonaState(const FSteamId SteamIdFriend);


	/**
	 * Gets a relationship to a specified user.
	 * 
	 * @param SteamIdFriend The Steam ID of the other user.
	 * @return How the users know each other.
	 */
	UFUNCTION()
	static ESteamFriendRelationship GetFriendRelationship(const FSteamId SteamIdFriend);


	/**
	 * Get a Rich Presence value from a specified friend.
	 * 
	 * @param SteamIdFriend The friend to get the Rich Presence value for.
	 * @param Key The Rich Presence key to request.
	 * @return Returns an empty string ("") if the specified key is not set.
	 */
	UFUNCTION()
	static FString GetFriendRichPresence(const FSteamId SteamIdFriend, const FString& Key);


	/**
	 * Get a Rich Presence value by its index, call GetFriendRichPresenceKeyCount to know the number of keys.
	 * 
	 * @param SteamIdFriend This should be the same user provided to the previous call to GetFriendRichPresenceKeyCount!
	 * @param KeyIndex An index between 0 and GetFriendRichPresenceKeyCount.
	 * @return Returns an empty string ("") if the index is invalid or the specified user has no Rich Presence data available.
	 */
	UFUNCTION()
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
	UFUNCTION()
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
	UFUNCTION()
	static int32 GetFriendsGroupCount();


	/**
	 * Gets the friends group ID for the given index.
	 *
	 * @note NOTE: You must call GetFriendsGroupCount before calling this.
	 * 
	 * @param FriendsGroupIndex An index between 0 and GetFriendsGroupCount.
	 * @return Invalid indices return an invalid FriendsGroupId.
	 */
	UFUNCTION()
	static FFriendsGroupId GetFriendsGroupIDByIndex(const int32 FriendsGroupIndex);


	/**
	 * Gets the number of friends in a given friends group.
	 *
	 * This should be called before getting the list of friends with GetFriendsGroupMembersList.
	 * 
	 * @param FriendsGroupId The friends group ID to get the number of friends in.
	 * @return The number of friends in the specified friends group.
	 */
	UFUNCTION()
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
	UFUNCTION()
	static void GetFriendsGroupMembersList(FFriendsGroupId FriendsGroupId, TArray<FSteamId>& SteamIdMembers, const int32 MembersCount);


	/**
	 * Gets the name for the given friends group.
	 * 
	 * @param FriendsGroupId The friends group ID to get the name of.
	 * @return The friend groups name in UTF-8 format. Returns NULL if the group ID is invalid.
	 */
	UFUNCTION()
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
	UFUNCTION()
	static int32 GetFriendSteamLevel(FSteamId SteamIdFriend);


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
	UFUNCTION()
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
	UFUNCTION()
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
	UFUNCTION()
	static FString GetPersonaName();


	/**
	 * Gets the friend status of the current user.
	 *
	 * To get the state of other users use GetFriendPersonaState.
	 * 
	 * @return The friend state of the current user. (Online, Offline, In-Game, etc)
	 */
	UFUNCTION()
	static ESteamPersonaState GetPersonaState();


	/**
	 * Gets the nickname that the current user has set for the specified user.
	 * 
	 * @param SteamIdPlayer The Steam ID of the user.
	 * @return Empty if the no nickname has been set for that user.
	 */
	UFUNCTION()
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
	UFUNCTION()
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
	UFUNCTION()
	static TSet<ESteamUserRestriction> GetUserRestrictions();

	UFUNCTION(BlueprintCallable)
	static TSet<ESteamUserRestriction> TestSteamUserRestrictions(const TSet<ESteamUserRestriction>& Restrictions);
};
