#pragma once

#include "CoreMinimal.h"
#include "Structs/AppId.h"
#include "DLCData.generated.h"


USTRUCT(BlueprintType)
struct FDLCData
{
	GENERATED_BODY()

	/** App ID of the DLC */
	UPROPERTY(BlueprintReadWrite, Category="SteamDome|SteamApps|DLC")
	FAppId AppId;

	/** Whether the DLC is currently available on the Steam store. Will be false if the DLC does not have a visible store page. */
	UPROPERTY(BlueprintReadWrite, Category="SteamDome|SteamApps|DLC")
	bool bAvailable = false;

	/** Returns the name of the DLC */
	UPROPERTY(BlueprintReadWrite, Category="SteamDome|SteamApps|DLC")
	FString Name;

	FDLCData() = default;
	FDLCData(const FAppId& AppId, const bool bAvailable, const FString& Name)
		: AppId(AppId), bAvailable(bAvailable), Name(Name)
		{}
};
