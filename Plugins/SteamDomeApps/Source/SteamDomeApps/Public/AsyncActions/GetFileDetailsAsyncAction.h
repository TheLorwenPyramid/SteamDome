// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <steam/isteamapps.h>
#include "Helpers/SteamCallResult.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GetFileDetailsAsyncAction.generated.h"


struct FFileDetailsResult;
struct FileDetailsResult_t;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGetFileDetailsSignature, const bool, bSuccess, const FFileDetailsResult&, FileDetails);


UCLASS()
class STEAMDOMEAPPS_API UGetFileDetailsAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<const UObject> WorldContext;

	FString Filename;

	STEAMDOME_CALLRESULT(FOnFileDetailsReady, FileDetailsResult_t)
	FOnFileDetailsReady SteamCallResult;

public:

	UPROPERTY(BlueprintAssignable)
	FOnGetFileDetailsSignature OnCompleted;

	/**
	 * Asynchronously retrieves metadata details about a specific file in the depot manifest.
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly, WorldContext="WorldContextObject"))
	static UGetFileDetailsAsyncAction* GetFileDetails(const UObject* WorldContextObject, const FString& Filename);

	virtual void Activate() override;

protected:
	
	void OnGetFileDetails(FileDetailsResult_t* FileDetailsResult, bool bIOFailure);
};
