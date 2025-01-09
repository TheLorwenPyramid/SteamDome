// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/SteamId.h"
#include <steam/isteamfriends.h>
#include "Helpers/SteamCallResult.h"
#include "Structs/ClanActivityCounts.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "DownloadClanActivityCountsAsyncAction.generated.h"


using FClanMap = TMap<FSteamId, FClanActivityCounts>;


USTRUCT(BlueprintType)
struct FClanActivityCountWithSteamId
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TMap<FSteamId, FClanActivityCounts> Clans;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FDownloadClanActivityCountsCompleted,
	const bool, bSuccess,
	const FClanActivityCountWithSteamId&, Clans
);

UCLASS()
class STEAMDOMEFRIENDS_API UDownloadClanActivityCountsAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<const UObject> WorldContext;

	UPROPERTY()
	TArray<FSteamId> Clans;

	STEAMDOME_CALLRESULT(FOnDownloadClanActivityCompleted, DownloadClanActivityCountsResult_t)
	FOnDownloadClanActivityCompleted OnDownloadClanActivityCompleted;

public:
	
	UPROPERTY(BlueprintAssignable)
	FDownloadClanActivityCountsCompleted OnCompleted;
	
	/**
	 * Refresh the Steam Group activity data or get the data from groups other than one that the current user is a member.
	 * 
	 * After receiving the callback you can then use GetClanActivityCounts to get the up-to-date user counts.
	 * @param WorldContextObject 
	 * @param SteamIdClans The list of clans to get updated information about.
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly, WorldContext="WorldContextObject"))
	static UDownloadClanActivityCountsAsyncAction* DownloadClanActivityCounts(
		const UObject* WorldContextObject, const TArray<FSteamId>& SteamIdClans
	);

	virtual void Activate() override;

protected:

	void OnClanActivityCountDownloaded(DownloadClanActivityCountsResult_t* Activity, bool bIOFailure);
};
