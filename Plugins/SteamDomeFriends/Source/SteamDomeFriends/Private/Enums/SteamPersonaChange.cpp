// Fill out your copyright notice in the Description page of Project Settings.


#include "Enums/SteamPersonaChange.h"


EPersonaChange PersonaChange::ToSteamEnum(const ESteamPersonaChange PersonaChange)
{
	switch (PersonaChange)
	{
	case ESteamPersonaChange::INVALID:
		checkNoEntry();
	case ESteamPersonaChange::Name:
		return EPersonaChange::k_EPersonaChangeName;
	case ESteamPersonaChange::Status:
		return EPersonaChange::k_EPersonaChangeName;
	case ESteamPersonaChange::ComeOnline:
		return EPersonaChange::k_EPersonaChangeComeOnline;
	case ESteamPersonaChange::GoneOffline:
		return EPersonaChange::k_EPersonaChangeGoneOffline;
	case ESteamPersonaChange::GamePlayed:
		return EPersonaChange::k_EPersonaChangeGamePlayed;
	case ESteamPersonaChange::GameServer:
		return EPersonaChange::k_EPersonaChangeGameServer;
	case ESteamPersonaChange::Avatar:
		return EPersonaChange::k_EPersonaChangeAvatar;
	case ESteamPersonaChange::JoinedSource:
		return EPersonaChange::k_EPersonaChangeJoinedSource;
	case ESteamPersonaChange::LeftSource:
		return EPersonaChange::k_EPersonaChangeLeftSource;
	case ESteamPersonaChange::RelationshipChanged:
		return EPersonaChange::k_EPersonaChangeRelationshipChanged;
	case ESteamPersonaChange::NameFirstSet:
		return EPersonaChange::k_EPersonaChangeNameFirstSet;
	case ESteamPersonaChange::Broadcast:
		return EPersonaChange::k_EPersonaChangeBroadcast;
	case ESteamPersonaChange::Nickname:
		return EPersonaChange::k_EPersonaChangeNickname;
	case ESteamPersonaChange::SteamLevel:
		return EPersonaChange::k_EPersonaChangeSteamLevel;
	case ESteamPersonaChange::RichPresence:
		return EPersonaChange::k_EPersonaChangeRichPresence;
	}

	checkNoEntry();
	return EPersonaChange::k_EPersonaChangeAvatar; // Should not be executed
}


bool PersonaChange::HasBitEnabled(const int32 Bitfield, const ESteamPersonaChange PersonaChange)
{
	return Bitfield & StaticCast<int32>(ToSteamEnum(PersonaChange));
}
