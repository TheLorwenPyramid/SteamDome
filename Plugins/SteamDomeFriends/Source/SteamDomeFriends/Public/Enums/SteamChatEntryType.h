#pragma once

#include "CoreMinimal.h"
#include "SteamChatEntryType.generated.h"


/**
 * Chat Entry Types.
 *
 * Returned by ISteamFriends::GetFriendMessage, ISteamFriends::GetClanChatMessage and
 * ISteamMatchmaking::GetLobbyChatEntry.
 */
UENUM(BlueprintType)
enum class ESteamChatEntryType : uint8
{
	Invalid = 0, // Invalid.
	ChatMsg = 1, // Normal text message from another user.
	Typing = 2, // The other user is typing, not used in multi-user chat.
	InviteGame = 3, // Invite from other user into that users current game.
	Emote = 4, // Text emote message (Deprecated, should be treated as ChatMsg).
	LeftConversation = 6, // A user has left the conversation (closed the chat window).
	Entered = 7, // User has entered the conversation, used in multi-user chat and group chat.
	WasKicked = 8, // User was kicked (Data: Steam ID of the user performing the kick).
	WasBanned = 9, // User was banned (Data: Steam ID of the user performing the ban).
	Disconnected = 10, // User disconnected.
	HistoricalChat = 11, // A chat message from user's chat history or offline message.
	LinkBlocked = 14, // A link was removed by the chat filter.
};
