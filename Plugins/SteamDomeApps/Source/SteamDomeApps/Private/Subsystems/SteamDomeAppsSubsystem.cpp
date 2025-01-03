// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/SteamDomeAppsSubsystem.h"

#include <steam/isteamapps.h>

#include "Wrappers/DepotId.h"
#include "Wrappers/SteamId.h"
#include "Wrappers/AppId.h"
#include "Wrappers/UInt64.h"


bool USteamDomeAppsSubsystem::GetDLCDataByIndex(const int32 DLCIndex, FAppId& AppId, bool& bAvailable, FString& Name, const int32 MaxExpectedLength) const
{
	char* Buffer = new char[MaxExpectedLength];

	const bool bSuccess = SteamApps()->BGetDLCDataByIndex(DLCIndex, &AppId.AppId, &bAvailable, Buffer, MaxExpectedLength);
	Name = FString(UTF8_TO_TCHAR(Buffer));

	return bSuccess;
}


bool USteamDomeAppsSubsystem::IsAppInstalled(const FAppId& AppId) const
{
	return SteamApps()->BIsAppInstalled(AppId.AppId);
}


bool USteamDomeAppsSubsystem::IsCybercafe() const
{
	return SteamApps()->BIsCybercafe();
}


bool USteamDomeAppsSubsystem::IsDLCInstalled(const FAppId& AppId) const
{
	return SteamApps()->BIsDlcInstalled(AppId.AppId);
}


bool USteamDomeAppsSubsystem::IsLowViolence() const
{
	return SteamApps()->BIsLowViolence();
}


bool USteamDomeAppsSubsystem::IsSubscribed() const
{
	return SteamApps()->BIsSubscribed();
}


bool USteamDomeAppsSubsystem::IsSubscribedApp(const FAppId& AppId) const
{
	return SteamApps()->BIsSubscribedApp(AppId.AppId);
}


bool USteamDomeAppsSubsystem::IsSubscribedFromFamilySharing() const
{
	return SteamApps()->BIsSubscribedFromFamilySharing();
}


bool USteamDomeAppsSubsystem::IsSubscribedFromFreeWeekend() const
{
	return SteamApps()->BIsSubscribedFromFreeWeekend();
}


bool USteamDomeAppsSubsystem::IsTimedTrial(int64& SecondsAllowed, int64& SecondsPlayed) const
{
	uint32 SecondsAllowedOut, SecondsPlayedOut;
	const bool bSuccess = SteamApps()->BIsTimedTrial(&SecondsAllowedOut, &SecondsPlayedOut);

	SecondsAllowed = SecondsAllowedOut;
	SecondsPlayed = SecondsPlayedOut;

	return bSuccess;
}


bool USteamDomeAppsSubsystem::IsVACBanned() const
{
	return SteamApps()->BIsVACBanned();
}


int32 USteamDomeAppsSubsystem::GetAppBuildId() const
{
	return SteamApps()->GetAppBuildId();
}


void USteamDomeAppsSubsystem::GetAppInstallDir(const FAppId& AppId, FString& Folder, const int32 MaxExpectedLength) const
{
	char* Buffer = new char[MaxExpectedLength];

	const uint32 Bytes = SteamApps()->GetAppInstallDir(AppId.AppId, Buffer, MaxExpectedLength);
	Folder = FString(UTF8_TO_TCHAR(Buffer), Bytes);
}


FSteamId USteamDomeAppsSubsystem::GetAppOwner() const
{
	return FSteamId::FromCSteamID(SteamApps()->GetAppOwner());
}


TArray<FString> USteamDomeAppsSubsystem::GetAvailableGameLanguages() const
{
	const FString LanguagesString = FString(SteamApps()->GetAvailableGameLanguages());
	
	TArray<FString> Languages;
	LanguagesString.ParseIntoArray(Languages, TEXT(","), true);

	return Languages;
}


bool USteamDomeAppsSubsystem::GetCurrentBetaName(FString& Name, const int32 MaxExpectedLength) const
{
	char* Buffer = new char[MaxExpectedLength];

	const bool bInBeta = SteamApps()->GetCurrentBetaName(Buffer, MaxExpectedLength);
	Name = FString(UTF8_TO_TCHAR(Buffer));

	return bInBeta;
}


FString USteamDomeAppsSubsystem::GetCurrentGameLanguage() const
{
	return FString(SteamApps()->GetCurrentGameLanguage());
}


int32 USteamDomeAppsSubsystem::GetDLCCount() const
{
	return SteamApps()->GetDLCCount();
}


bool USteamDomeAppsSubsystem::GetDLCDownloadProgress(const FAppId& AppId, FUInt64& BytesDownloaded, FUInt64& BytesTotal) const
{
	return SteamApps()->GetDlcDownloadProgress(AppId.AppId, &BytesDownloaded.Value, &BytesTotal.Value);
}


FDateTime USteamDomeAppsSubsystem::GetEarliestPurchaseUnixTime(const FAppId& AppId) const
{
	const uint32 UnixTime = SteamApps()->GetEarliestPurchaseUnixTime(AppId.AppId);
	return FDateTime::FromUnixTimestamp(UnixTime);
}


TArray<FDepotId> USteamDomeAppsSubsystem::GetInstalledDepots(const FAppId& AppId, const int64 MaxDepots) const
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


FString USteamDomeAppsSubsystem::GetLaunchCommandLine(const int32 MaxExpectedLength) const
{
	char* Buffer = new char[MaxExpectedLength];

	const int32 Bytes = SteamApps()->GetLaunchCommandLine(Buffer, MaxExpectedLength);
	return FString(UTF8_TO_TCHAR(Buffer), Bytes);
}


FString USteamDomeAppsSubsystem::GetLaunchQueryParam(const FString& Key) const
{
	return FString(SteamApps()->GetLaunchQueryParam(TCHAR_TO_UTF8(*Key)));
}


void USteamDomeAppsSubsystem::InstallDLC(const FAppId& AppId) const
{
	SteamApps()->InstallDLC(AppId.AppId);
}


bool USteamDomeAppsSubsystem::MarkContentCorrupt(const bool bMissingFilesOnly) const
{
	return SteamApps()->MarkContentCorrupt(bMissingFilesOnly);
}


void USteamDomeAppsSubsystem::UninstallDLC(const FAppId& AppId) const
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
