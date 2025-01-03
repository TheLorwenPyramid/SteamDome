// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Result.h"
#include "Structs/UInt64.h"
#include "UObject/Object.h"
#include "FileDetailsResult.generated.h"


struct FileDetailsResult_t;

/**
 * Resulting data from calling GetFileResult.
 */
USTRUCT(BlueprintType)
struct STEAMDOMEAPPS_API FFileDetailsResult
{
	GENERATED_BODY()

	FFileDetailsResult()
		: Result(ESteamResult::None), FileSize(0), FileSHA(""), Flags(0)
	{}

	FFileDetailsResult(const FileDetailsResult_t& Details);

	/**
	 * Was the call successful? k_EResultOK if it was;
	 * otherwise, k_EResultFileNotFound if the file was not found.
	 * None of the other fields are filled out if the call was not successful.
	 */
	UPROPERTY(BlueprintReadOnly)
	ESteamResult Result;

	/** Original file size in bytes */
	UPROPERTY(BlueprintReadOnly)
	FUInt64 FileSize;

	/** Original file SHA1 hash */
	UPROPERTY(BlueprintReadOnly)
	FString FileSHA;

	/** Undocumented */
	UPROPERTY(BlueprintReadOnly)
	int64 Flags;
};
