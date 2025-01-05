// Fill out your copyright notice in the Description page of Project Settings.


#include "Structs/FriendGameInfo.h"

#include <steam/isteamfriends.h>


FFriendGameInfo::FFriendGameInfo(const FriendGameInfo_t& FriendGameInfo)
	: GameId(FriendGameInfo.m_gameID),
	GameIP(FriendGameInfo.m_unGameIP),
	GamePort(FriendGameInfo.m_usGamePort),
	QueryPort(FriendGameInfo.m_usQueryPort),
	SteamIdLobby(FriendGameInfo.m_steamIDLobby)
{
}
