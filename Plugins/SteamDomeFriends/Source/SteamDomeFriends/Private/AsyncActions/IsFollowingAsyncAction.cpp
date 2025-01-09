// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/IsFollowingAsyncAction.h"

#include "Subsystems/SteamDomeFriendsSubsystem.h"


UIsFollowingAsyncAction* UIsFollowingAsyncAction::IsFollowing(const UObject* WorldContextObject, const FSteamId SteamId)
{
	auto* Instance = NewObject<UIsFollowingAsyncAction>();
	Instance->WorldContext = WorldContextObject;
	Instance->SteamId = SteamId;

	Instance->RegisterWithGameInstance(WorldContextObject);

	return Instance;
}


void UIsFollowingAsyncAction::Activate()
{
	Super::Activate();

	IsFollowingCallback.Init(
		FIsFollowingCallbackDelegate::CreateUObject(this, &ThisClass::OnIsFollowingCompleted)
	);

	const auto Handle = SteamFriends()->IsFollowing(SteamId.GetCSteamID());
	
}


void UIsFollowingAsyncAction::OnIsFollowingCompleted(FriendsIsFollowing_t* FriendsIsFollowing, const bool bIOFailure)
{
	if (bIOFailure || !FriendsIsFollowing || FriendsIsFollowing->m_eResult != k_EResultOK)
	{
		OnCompleted.Broadcast(false, false);
	}
	else
	{
		OnCompleted.Broadcast(true, FriendsIsFollowing->m_bIsFollowing);
	}

	SetReadyToDestroy();
}
