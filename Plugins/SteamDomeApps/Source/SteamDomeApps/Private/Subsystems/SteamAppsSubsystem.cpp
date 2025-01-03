// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/SteamAppsSubsystem.h"

#include <steam/isteamapps.h>

#include "Structs/AppId.h"
#include "Structs/UInt64.h"
#include "Structs/SteamId.h"
#include "Structs/DepotId.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/DLCData.h"


USteamAppsSubsystem* USteamAppsSubsystem::Get(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<USteamAppsSubsystem>();
}


void USteamAppsSubsystem::GetDLCDataByIndex(
	const int32 DLCIndex, bool& bExists, FDLCData& DLCData, const int32 MaxExpectedLength
) {
	char* Buffer = new char[MaxExpectedLength];

	bExists = SteamApps()->BGetDLCDataByIndex(DLCIndex, &DLCData.AppId.AppId, &DLCData.bAvailable, Buffer, MaxExpectedLength);
	DLCData.Name = FString(UTF8_TO_TCHAR(Buffer));
}

/*
bool USteamAppsSubsystem::GetDLCDataByIndex(const int32 DLCIndex, FAppId& AppId, bool& bAvailable, FString& Name, const int32 MaxExpectedLength)
{
	char* Buffer = new char[MaxExpectedLength];

	const bool bSuccess = SteamApps()->BGetDLCDataByIndex(DLCIndex, &AppId.AppId, &bAvailable, Buffer, MaxExpectedLength);
	Name = FString(UTF8_TO_TCHAR(Buffer));

	return bSuccess;
}
*/

bool USteamAppsSubsystem::IsAppInstalled(const FAppId& AppId)
{
	return SteamApps()->BIsAppInstalled(AppId.AppId);
}


bool USteamAppsSubsystem::IsCybercafe()
{
	return SteamApps()->BIsCybercafe();
}


bool USteamAppsSubsystem::IsDLCInstalled(const FAppId& AppId)
{
	return SteamApps()->BIsDlcInstalled(AppId.AppId);
}


bool USteamAppsSubsystem::IsLowViolence()
{
	return SteamApps()->BIsLowViolence();
}


bool USteamAppsSubsystem::IsSubscribed()
{
	return SteamApps()->BIsSubscribed();
}


bool USteamAppsSubsystem::IsSubscribedApp(const FAppId& AppId)
{
	return SteamApps()->BIsSubscribedApp(AppId.AppId);
}


bool USteamAppsSubsystem::IsSubscribedFromFamilySharing()
{
	return SteamApps()->BIsSubscribedFromFamilySharing();
}


bool USteamAppsSubsystem::IsSubscribedFromFreeWeekend()
{
	return SteamApps()->BIsSubscribedFromFreeWeekend();
}


bool USteamAppsSubsystem::IsTimedTrial(int64& SecondsAllowed, int64& SecondsPlayed)
{
	uint32 SecondsAllowedOut, SecondsPlayedOut;
	const bool bSuccess = SteamApps()->BIsTimedTrial(&SecondsAllowedOut, &SecondsPlayedOut);

	SecondsAllowed = SecondsAllowedOut;
	SecondsPlayed = SecondsPlayedOut;

	return bSuccess;
}


bool USteamAppsSubsystem::IsVACBanned()
{
	return SteamApps()->BIsVACBanned();
}


int32 USteamAppsSubsystem::GetAppBuildId()
{
	return SteamApps()->GetAppBuildId();
}


void USteamAppsSubsystem::GetAppInstallDir(const FAppId& AppId, FString& Folder, const int32 MaxExpectedLength)
{
	char* Buffer = new char[MaxExpectedLength];

	const uint32 Bytes = SteamApps()->GetAppInstallDir(AppId.AppId, Buffer, MaxExpectedLength);
	Folder = FString(UTF8_TO_TCHAR(Buffer), Bytes);
}


FSteamId USteamAppsSubsystem::GetAppOwner()
{
	return FSteamId::FromCSteamID(SteamApps()->GetAppOwner());
}


TArray<FString> USteamAppsSubsystem::GetAvailableGameLanguages()
{
	const FString LanguagesString = FString(SteamApps()->GetAvailableGameLanguages());
	
	TArray<FString> Languages;
	LanguagesString.ParseIntoArray(Languages, TEXT(","), true);

	return Languages;
}


bool USteamAppsSubsystem::GetCurrentBetaName(FString& Name, const int32 MaxExpectedLength)
{
	char* Buffer = new char[MaxExpectedLength];

	const bool bInBeta = SteamApps()->GetCurrentBetaName(Buffer, MaxExpectedLength);
	Name = FString(UTF8_TO_TCHAR(Buffer));

	return bInBeta;
}


FString USteamAppsSubsystem::GetCurrentGameLanguage()
{
	return FString(SteamApps()->GetCurrentGameLanguage());
}


int32 USteamAppsSubsystem::GetDLCCount()
{
	return SteamApps()->GetDLCCount();
}


bool USteamAppsSubsystem::GetDLCDownloadProgress(const FAppId& AppId, FUInt64& BytesDownloaded, FUInt64& BytesTotal)
{
	return SteamApps()->GetDlcDownloadProgress(AppId.AppId, &BytesDownloaded.Value, &BytesTotal.Value);
}


FDateTime USteamAppsSubsystem::GetEarliestPurchaseUnixTime(const FAppId& AppId)
{
	const uint32 UnixTime = SteamApps()->GetEarliestPurchaseUnixTime(AppId.AppId);
	return FDateTime::FromUnixTimestamp(UnixTime);
}


TArray<FDepotId> USteamAppsSubsystem::GetInstalledDepots(const FAppId& AppId, const int64 MaxDepots)
{
	TArray<DepotId_t> Depots;
	Depots.Reserve(MaxDepots);
	
	const uint32 Num = SteamApps()->GetInstalledDepots(AppId.AppId, Depots.GetData(), MaxDepots);

	TArray<FDepotId> DepotsProcessed;
	DepotsProcessed.SetNum(Num);
	for (uint32 i = 0; i < Num; i++)
	{
		DepotsProcessed[i] = FDepotId{ Depots[i] };
	}

	return DepotsProcessed;
}


/*
void USteamAppsSubsystem::GetFileDetails(const FString& Filename)
{
	const auto ApiCallId = SteamApps()->GetFileDetails(TCHAR_TO_UTF8(*Filename));
	OnGetFileDetailsFinished.Set(ApiCallId, this, &ThisClass::OnGetFileDetails);
}
*/


FString USteamAppsSubsystem::GetLaunchCommandLine(const int32 MaxExpectedLength)
{
	char* Buffer = new char[MaxExpectedLength];

	const int32 Bytes = SteamApps()->GetLaunchCommandLine(Buffer, MaxExpectedLength);
	return FString(UTF8_TO_TCHAR(Buffer), Bytes);
}


FString USteamAppsSubsystem::GetLaunchQueryParam(const FString& Key)
{
	return FString(SteamApps()->GetLaunchQueryParam(TCHAR_TO_UTF8(*Key)));
}


void USteamAppsSubsystem::InstallDLC(const FAppId& AppId)
{
	SteamApps()->InstallDLC(AppId.AppId);
}


bool USteamAppsSubsystem::MarkContentCorrupt(const bool bMissingFilesOnly)
{
	return SteamApps()->MarkContentCorrupt(bMissingFilesOnly);
}


void USteamAppsSubsystem::UninstallDLC(const FAppId& AppId)
{
	return SteamApps()->UninstallDLC(AppId.AppId);
}


void USteamAppsSubsystem::OnDLCInstalledCallback(DlcInstalled_t* pParam)
{
	if (pParam)
	{
		OnDLCInstalled.Broadcast(FAppId(pParam->m_nAppID));
	}
}
