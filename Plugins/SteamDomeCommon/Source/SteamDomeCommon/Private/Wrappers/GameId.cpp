// Fill out your copyright notice in the Description page of Project Settings.

#include "Structs/GameId.h"


FGameId FGameId::FromCGameID(const CGameID& GameId)
{
	return FGameId(GameId);
}


const CGameID& FGameId::GetGameId() const
{
	return UnderlyingGameId;
}


CGameID& FGameId::GetGameId()
{
	return UnderlyingGameId;
}


FString FGameId::ToString() const
{
	return FString::Printf(TEXT("%llu"), UnderlyingGameId.ToUint64());
}


bool FGameId::IsValid() const
{
	return UnderlyingGameId.IsValid();
}
