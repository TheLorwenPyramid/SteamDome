// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/SteamId.h"
#include <steam/isteamfriends.h>
#include "Helpers/SteamCallResult.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GetFollowerCountAsyncAction.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnGetFollowerCountCompletedSignature, const bool, bSuccess, const int32, Count
);

/**
 * 
 */
UCLASS()
class STEAMDOMEFRIENDS_API UGetFollowerCountAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	STEAMDOME_CALLRESULT(FSteamFollowerCountCall, FriendsGetFollowerCount_t)
	FSteamFollowerCountCall SteamFollowerCountCall;

	UPROPERTY()
	TObjectPtr<const UObject> WorldContext;
	
	FSteamId SteamId;

public:

	UPROPERTY(BlueprintAssignable)
	FOnGetFollowerCountCompletedSignature OnCompleted;

	/**
	 * Gets the number of users following the specified user.
	 * 
	 * @param WorldContextObject 
	 * @param SteamId Target SteamId. 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", WorldContext="WorldContextObject"))
	static UGetFollowerCountAsyncAction* GetFollowerCount(
		const UObject* WorldContextObject, const FSteamId SteamId
	);

	virtual void Activate() override;

protected:

	void OnSteamFollowerCountCompleted(FriendsGetFollowerCount_t* FollowerCount, bool bIOFailure);
};
