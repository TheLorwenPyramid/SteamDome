// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/GetFollowerCountAsyncAction.h"

#include "Subsystems/SteamDomeFriendsSubsystem.h"


UGetFollowerCountAsyncAction* UGetFollowerCountAsyncAction::GetFollowerCount(
	const UObject* WorldContextObject, const FSteamId SteamId
) {
	auto* Instance = NewObject<ThisClass>();
	Instance->WorldContext = WorldContextObject;
	Instance->SteamId = SteamId;

	Instance->RegisterWithGameInstance(WorldContextObject);
	
	return Instance;
}


void UGetFollowerCountAsyncAction::Activate()
{
	Super::Activate();

	SteamFollowerCountCall.Init(
		FSteamFollowerCountCallDelegate::CreateUObject(this, &UGetFollowerCountAsyncAction::OnSteamFollowerCountCompleted)
	);

	const auto CallId = SteamFriends()->GetFollowerCount(SteamId.GetCSteamID());
	if (!SteamFollowerCountCall.Bind(CallId))
	{
		OnCompleted.Broadcast(false, 0);
		SetReadyToDestroy();
	}
}


void UGetFollowerCountAsyncAction::OnSteamFollowerCountCompleted(
	FriendsGetFollowerCount_t* FollowerCount, bool bIOFailure
) {
	if (bIOFailure || !FollowerCount)
	{
		OnCompleted.Broadcast(false, 0);
	}
	else
	{
		check(FollowerCount->m_steamID == SteamId.GetCSteamID());
		
		OnCompleted.Broadcast(true, FollowerCount->m_nCount);
	}

	SetReadyToDestroy();
}
