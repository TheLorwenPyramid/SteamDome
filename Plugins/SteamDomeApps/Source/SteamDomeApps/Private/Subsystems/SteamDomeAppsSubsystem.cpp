// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/SteamDomeAppsSubsystem.h"

#include <steam/isteamapps.h>
#include <steam/isteamutils.h>

#include "Structs/AppId.h"
#include "Structs/UInt64.h"
#include "Structs/SteamId.h"
#include "Structs/DepotId.h"
#include "Structs/DLCData.h"
#include "Helpers/TempString.h"
#include "Kismet/GameplayStatics.h"


USteamDomeAppsSubsystem* USteamDomeAppsSubsystem::Get(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<USteamDomeAppsSubsystem>();
}


void USteamDomeAppsSubsystem::GetDLCDataByIndex(
	const int32 DLCIndex, bool& bExists, FDLCData& DLCData, const int32 MaxExpectedLength
) {
	const FTempString TempString(MaxExpectedLength);

	bExists = SteamApps()->BGetDLCDataByIndex(DLCIndex, &DLCData.AppId.AppId, &DLCData.bAvailable, TempString.Start(), MaxExpectedLength);
	DLCData.Name = TempString.ToString();
}


bool USteamDomeAppsSubsystem::IsAppInstalled(const FAppId AppId)
{
	return SteamApps()->BIsAppInstalled(AppId.AppId);
}


bool USteamDomeAppsSubsystem::IsCybercafe()
{
	return SteamApps()->BIsCybercafe();
}


bool USteamDomeAppsSubsystem::IsDLCInstalled(const FAppId AppId)
{
	return SteamApps()->BIsDlcInstalled(AppId.AppId);
}


bool USteamDomeAppsSubsystem::IsLowViolence()
{
	return SteamApps()->BIsLowViolence();
}


bool USteamDomeAppsSubsystem::IsSubscribed()
{
	return SteamApps()->BIsSubscribed();
}


bool USteamDomeAppsSubsystem::IsSubscribedApp(const FAppId AppId)
{
	return SteamApps()->BIsSubscribedApp(AppId.AppId);
}


bool USteamDomeAppsSubsystem::IsSubscribedFromFamilySharing()
{
	return SteamApps()->BIsSubscribedFromFamilySharing();
}


bool USteamDomeAppsSubsystem::IsSubscribedFromFreeWeekend()
{
	return SteamApps()->BIsSubscribedFromFreeWeekend();
}


bool USteamDomeAppsSubsystem::IsTimedTrial(int64& SecondsAllowed, int64& SecondsPlayed)
{
	uint32 SecondsAllowedOut, SecondsPlayedOut;
	const bool bSuccess = SteamApps()->BIsTimedTrial(&SecondsAllowedOut, &SecondsPlayedOut);

	SecondsAllowed = SecondsAllowedOut;
	SecondsPlayed = SecondsPlayedOut;

	return bSuccess;
}


bool USteamDomeAppsSubsystem::IsVACBanned()
{
	return SteamApps()->BIsVACBanned();
}


int32 USteamDomeAppsSubsystem::GetAppBuildId()
{
	return SteamApps()->GetAppBuildId();
}


void USteamDomeAppsSubsystem::GetAppInstallDir(const FAppId AppId, FString& Folder, const int32 MaxExpectedLength)
{
	const FTempString TempString(MaxExpectedLength);

	const uint32 Bytes = SteamApps()->GetAppInstallDir(AppId.AppId, TempString.Start(), MaxExpectedLength);
	Folder = TempString.ToString();
}


FSteamId USteamDomeAppsSubsystem::GetAppOwner()
{
	return FSteamId::FromCSteamID(SteamApps()->GetAppOwner());
}


TArray<FString> USteamDomeAppsSubsystem::GetAvailableGameLanguages()
{
	const FString LanguagesString = FString(UTF8_TO_TCHAR(SteamApps()->GetAvailableGameLanguages()));
	
	TArray<FString> Languages;
	LanguagesString.ParseIntoArray(Languages, TEXT(","), true);

	return Languages;
}


bool USteamDomeAppsSubsystem::GetCurrentBetaName(FString& Name, const int32 MaxExpectedLength)
{
	const FTempString TempString(MaxExpectedLength);

	const bool bInBeta = SteamApps()->GetCurrentBetaName(TempString.Start(), MaxExpectedLength);
	Name = TempString.ToString();

	return bInBeta;
}


FString USteamDomeAppsSubsystem::GetCurrentGameLanguage()
{
	return FString(UTF8_TO_TCHAR(SteamApps()->GetCurrentGameLanguage()));
}


int32 USteamDomeAppsSubsystem::GetDLCCount()
{
	return SteamApps()->GetDLCCount();
}


bool USteamDomeAppsSubsystem::GetDLCDownloadProgress(const FAppId AppId, FUInt64& BytesDownloaded, FUInt64& BytesTotal)
{
	return SteamApps()->GetDlcDownloadProgress(AppId.AppId, &BytesDownloaded.Value, &BytesTotal.Value);
}


FDateTime USteamDomeAppsSubsystem::GetEarliestPurchaseUnixTime(const FAppId AppId)
{
	const uint32 UnixTime = SteamApps()->GetEarliestPurchaseUnixTime(AppId.AppId);
	return FDateTime::FromUnixTimestamp(UnixTime);
}


TArray<FDepotId> USteamDomeAppsSubsystem::GetInstalledDepots(const FAppId AppId, const int64 MaxDepots)
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


FString USteamDomeAppsSubsystem::GetLaunchCommandLine(const int32 MaxExpectedLength)
{
	const FTempString TempString(MaxExpectedLength);
	const int32 Bytes = SteamApps()->GetLaunchCommandLine(TempString.Start(), MaxExpectedLength);
	
	return TempString.ToString();
}


FString USteamDomeAppsSubsystem::GetLaunchQueryParam(const FString& Key)
{
	return FString(UTF8_TO_TCHAR(SteamApps()->GetLaunchQueryParam(TCHAR_TO_UTF8(*Key))));
}


void USteamDomeAppsSubsystem::InstallDLC(const FAppId AppId)
{
	SteamApps()->InstallDLC(AppId.AppId);
}


bool USteamDomeAppsSubsystem::MarkContentCorrupt(const bool bMissingFilesOnly)
{
	return SteamApps()->MarkContentCorrupt(bMissingFilesOnly);
}


void USteamDomeAppsSubsystem::UninstallDLC(const FAppId AppId)
{
	return SteamApps()->UninstallDLC(AppId.AppId);
}


void USteamDomeAppsSubsystem::OnDLCInstalledCallback(DlcInstalled_t* pParam)
{
	if (pParam)
	{
		OnDLCInstalled.Broadcast(FAppId(pParam->m_nAppID));
	}
}
