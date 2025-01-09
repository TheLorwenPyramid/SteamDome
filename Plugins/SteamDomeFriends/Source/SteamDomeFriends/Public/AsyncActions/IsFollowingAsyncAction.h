// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/SteamId.h"
#include <steam/isteamfriends.h>
#include "Helpers/SteamCallResult.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "IsFollowingAsyncAction.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FIsFollowingCompletedSignature,
	const bool, bSuccess,
	const bool, bIsFollowing
);

/**
 * 
 */
UCLASS()
class STEAMDOMEFRIENDS_API UIsFollowingAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	STEAMDOME_CALLRESULT(FIsFollowingCallback, FriendsIsFollowing_t)
	FIsFollowingCallback IsFollowingCallback;

	UPROPERTY()
	TObjectPtr<const UObject> WorldContext;

	FSteamId SteamId;

public:
	
	UPROPERTY(BlueprintAssignable)
	FIsFollowingCompletedSignature OnCompleted;


	/**
	 * Checks if the current user is following the specified user.
	 * 
	 * @param WorldContextObject 
	 * @param SteamId Target SteamId.
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", WorldContext="WorldContextObject"))
	static UIsFollowingAsyncAction* IsFollowing(
		const UObject* WorldContextObject, const FSteamId SteamId
	);

	virtual void Activate() override;

protected:

	void OnIsFollowingCompleted(FriendsIsFollowing_t* FriendsIsFollowing, const bool bIOFailure);
};
