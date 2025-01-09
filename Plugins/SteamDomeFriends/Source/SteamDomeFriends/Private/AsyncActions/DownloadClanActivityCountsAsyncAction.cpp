// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/DownloadClanActivityCountsAsyncAction.h"

#include "Subsystems/SteamDomeFriendsSubsystem.h"


UDownloadClanActivityCountsAsyncAction* UDownloadClanActivityCountsAsyncAction::DownloadClanActivityCounts(
	const UObject* WorldContextObject, const TArray<FSteamId>& SteamIdClans
) {
	auto* Instance = NewObject<UDownloadClanActivityCountsAsyncAction>();
	Instance->WorldContext = WorldContextObject;
	Instance->Clans = SteamIdClans;

	Instance->RegisterWithGameInstance(WorldContextObject);

	return Instance;
}


void UDownloadClanActivityCountsAsyncAction::Activate()
{
	Super::Activate();

	OnDownloadClanActivityCompleted.Init(
		FOnDownloadClanActivityCompletedDelegate::CreateUObject(this, &ThisClass::OnClanActivityCountDownloaded)
	);

	// Manually process each SteamId to make sure the copying is valid
	// in case in the future, the SteamId changes its contents
	TArray<CSteamID> SteamIds;
	SteamIds.SetNumUninitialized(Clans.Num());
	for (int32 i = 0; i < Clans.Num(); i++)
	{
		SteamIds[i] = Clans[i].GetCSteamID();
	}

	UE_LOG(LogTemp, Error, TEXT("Requesting %d clans"), SteamIds.Num());

	const auto CallId = SteamFriends()->DownloadClanActivityCounts(SteamIds.GetData(), Clans.Num());
	if (!OnDownloadClanActivityCompleted.Bind(CallId))
	{
		OnCompleted.Broadcast(false, {});
		SetReadyToDestroy();

		UE_LOG(LogTemp, Error, TEXT("Cancelled"));
	}

	UE_LOG(LogTemp, Error, TEXT("Activated: %llu"), CallId);
}


void UDownloadClanActivityCountsAsyncAction::OnClanActivityCountDownloaded(
	DownloadClanActivityCountsResult_t* Activity, bool bIOFailure
) {
	UE_LOG(LogTemp, Error, TEXT("OnClanActivityCountDownloaded"));
	
	if (bIOFailure || !Activity || !Activity->m_bSuccess)
	{
		OnCompleted.Broadcast(false, {});
		SetReadyToDestroy();
		return;
	}

	FClanActivityCounts ClanActivityCounts;
	TMap<FSteamId, FClanActivityCounts> SteamClans;
	for (const auto& ClanSteamId : Clans)
	{
		if (USteamDomeFriendsSubsystem::GetClanActivityCounts(ClanSteamId, ClanActivityCounts))
		{
			SteamClans.Add(ClanSteamId, ClanActivityCounts);
		}
	}

	OnCompleted.Broadcast(true, { SteamClans });
	SetReadyToDestroy();
}
