// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <steam/steam_api_common.h>
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

	TUniquePtr<struct FGetFileDetailsInternal> GetFileDetailsInternal = nullptr;

public:

	UPROPERTY(BlueprintAssignable)
	FOnGetFileDetailsSignature OnCompleted;

	/**
	 * Asynchronously retrieves metadata details about a specific file in the depot manifest.
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly, WorldContext="WorldContextObject"))
	static UGetFileDetailsAsyncAction* GetFileDetails(const UObject* WorldContextObject, const FString& Filename);

	virtual void Activate() override;

	virtual void SetReadyToDestroy() override;

protected:
	
	void OnGetFileDetails(FileDetailsResult_t* FileDetailsResult, bool bIOFailure);
};


DECLARE_DELEGATE_TwoParams(FOnGetFileDetailsInternalSignature, FileDetailsResult_t* FileDetailsResult, bool bIOFailure);


// Moved Steam handling logic to a different class to solve some issues compiling CCallResult
struct STEAMDOMEAPPS_API FGetFileDetailsInternal
{
	FOnGetFileDetailsInternalSignature OnGetFileDetailsEvent;
	
	void GetFileDetails(const FString& Filename);

protected:
	
	void OnGetFileDetails(FileDetailsResult_t* FileDetailsResult, bool bIOFailure);
	CCallResult<FGetFileDetailsInternal, FileDetailsResult_t> OnGetFileDetailsFinished;
};
