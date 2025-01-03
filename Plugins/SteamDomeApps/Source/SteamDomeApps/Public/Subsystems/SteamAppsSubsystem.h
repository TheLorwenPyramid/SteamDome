// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <steam/isteamapps.h>
#include "Structs/AppId.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SteamAppsSubsystem.generated.h"

struct FUInt64;
struct FDepotId;
struct FSteamId;
struct FDLCData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDLCInstalledSignature, const FAppId, AppId);

UCLASS()
class STEAMDOMEAPPS_API USteamAppsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:

	STEAM_CALLBACK(USteamAppsSubsystem, OnDLCInstalledCallback, DlcInstalled_t);

public:

	/** Triggered after the current user gains ownership of DLC and that DLC is installed. */
	UPROPERTY(BlueprintAssignable, Category="SteamDome|SteamApps", DisplayName="On DLC Installed")
	FDLCInstalledSignature OnDLCInstalled;

	/** Helper method to quickly get the SteamDomeApps Subsystem */
	static USteamAppsSubsystem* Get(const UObject* WorldContextObject);

	/** UNTESTED */
	/**
	 * Returns metadata for DLC by index, of range [0, GetDLCCount()]
	 * 
	 * @param DLCIndex Index of the DLC to get between 0 and GetDLCCount.
	 * @param bExists true if the current App ID has DLC's associated with it and iDLC falls between the range of 0 to GetDLCCount, otherwise false.
	 * @param DLCData Data of the DLC (AppId, Name, Availability).
	 * @param MaxExpectedLength Maximum length of the expected Name, used to reserve memory for the string.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps", DisplayName="Get DLC Data By Index", meta=(AdvancedDisplay="MaxExpectedLength"))
	static void GetDLCDataByIndex(const int32 DLCIndex, bool& bExists, FDLCData& DLCData, const int32 MaxExpectedLength = 128);

	/** UNTESTED */
	/**
	* Checks if a specific app is installed.
	* 
	* The app may not actually be owned by the current user, they may have it left over from a free weekend, etc.
	* 
	* This only works for base applications, not Downloadable Content (DLC). Use BIsDlcInstalled for DLC instead.
	* 
	* @param AppId The App ID of the application to check.
	* @return true if the specified App ID is installed; otherwise, false.
	*/
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static bool IsAppInstalled(const FAppId& AppId);
	
	/** UNTESTED */
	/**
	 * Deprecated - No longer used.
	 * Checks whether the current App ID is for Cyber Cafes.
	 * @return true if the license is for cyber cafe's; otherwise, false.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps", meta=(DeprecatedFunction))
	static bool IsCybercafe();

	/** UNTESTED */
	/**
	 * Takes AppID of DLC and checks if the user owns the DLC & if the DLC is installed.
	 *
	 * @note Should only be used for simple client side checks - not intended for granting in-game items.
	 * 
	 * @param AppId The App ID of the DLC to check.
	 * @return true if the user owns the DLC and it's currently installed, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps", DisplayName="Is DLC Installed")
	static bool IsDLCInstalled(const FAppId& AppId);

	/** UNTESTED */
	/**
	 * Checks if the license owned by the user provides low violence depots.
	 * 
	 * Low violence depots are useful for copies sold in countries that have content restrictions.
	 *
	 * @return true if the license owned by the user provides low violence depots; otherwise, false.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static bool IsLowViolence();

	/** UNTESTED */
	/**
	 * Checks if the active user is subscribed to the current App ID.
	 *
	 * @note This will always return true if you're using Steam DRM or calling SteamAPI_RestartAppIfNecessary.
	 * @return true if the active user owns the current AppId, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static bool IsSubscribed();

	/** UNTESTED */
	/**
	 * Checks if the active user is subscribed to a specified AppId.
	 * 
	 * Only use this if you need to check ownership of another game related to yours, a demo for example.
	 * @param AppId The App ID to check.
	 * @return true if the active user is subscribed to the specified App ID, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static bool IsSubscribedApp(const FAppId& AppId);

	/** UNTESTED */
	/**
	 * Checks if the active user is accessing the current appID via a temporary Family Shared license owned by another user.
	 * 
	 * If you need to determine the steamID of the permanent owner of the license, use GetAppOwner.
	 * 
	 * @return true if the active user is accessing the current appID via family sharing, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static bool IsSubscribedFromFamilySharing();

	/** UNTESTED */
	/**
	 *  Checks if the user is subscribed to the current app through a free weekend.
	 *  
	 *  Before using this please contact a Valve technical account manager via the Steamworks Discussion Board to properly package and secure your free weekend.
	 *  
	 * @return true if the active user is subscribed to the current App Id via a free weekend otherwise false any other type of license.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static bool IsSubscribedFromFreeWeekend();

	/** UNTESTED */
	/**
	 * Checks if the user is subscribed to the current appID through a timed trial.
	 * If so, returns true and gives back the total time the timed trial is allowed to play,
	 * along with the current amount of time the user has played.
	 * 
	 * @param SecondsAllowed Returns the number of seconds the timed trial will list.
	 * @param SecondsPlayed Returns the number of seconds that the user has played so far.
	 * @return true if the active user is subscribed to the current appID via a timed trial otherwise false any other type of license.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static bool IsTimedTrial(int64& SecondsAllowed, int64& SecondsPlayed);

	/** UNTESTED */
	/**
	 * Checks if the user has a VAC ban on their account.
	 *
	 * @return true if the user has a VAC ban on their account; otherwise, false.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps", DisplayName="Is VAC Banned")
	static bool IsVACBanned();

	/** UNTESTED */
	/**
	 * Gets the buildid of this app, may change at any time based on backend updates to the game.
	 * 
	 * @return The current Build Id of this App. Defaults to 0 if you're not running a build downloaded from steam.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static int32 GetAppBuildId();

	/** UNTESTED */
	/**
	 * Gets the install folder for a specific AppID.
	 *
	 * This works even if the application is not installed, based on where the game would be installed with the default Steam library location.
	 * 
	 * @param AppId The App ID to get the install dir for.
	 * @param Folder The string that the folder path will be copied into.
	 * @param MaxExpectedLength Maximum length of the expected Name, used to reserve memory for the string.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps", meta=(AdvancedDisplay="MaxExpectedLength"))
	static void GetAppInstallDir(const FAppId& AppId, FString& Folder, const int32 MaxExpectedLength = 128);

	/** UNTESTED */
	/**
	 * Gets the Steam ID of the true owner of the current app.
	 * This is different from the current user if they are accessing this app via Family Sharing.
	 * 
	 * @return The original owner of the current app.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static FSteamId GetAppOwner();

	/** UNTESTED */
	/**
	 * Gets a list of the languages the current app supports.
	 * For the full list of languages that may be returned see "Localization and Languages" in Steamworks docs.
	 * 
	 * @return A list of languages.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static TArray<FString> GetAvailableGameLanguages();

	/** UNTESTED */
	/**
	 * Checks if the user is running from a beta branch, and gets the name of the branch if they are.
	 * 
	 * @param Name The string where the beta name will be copied in to.
	 * @param MaxExpectedLength Maximum length of the expected Name, used to reserve memory for the string.
	 * @return true if the user is on a beta branch; otherwise, false.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps", meta=(AdvancedDisplay="MaxExpectedLength"))
	static bool GetCurrentBetaName(FString& Name, int32 MaxExpectedLength = 128);

	// These three are unavailable in the Unreal's version of the header
	// int GetNumBetas(int32& Available, int32& Private);
	// bool GetBetaInfo(int32 BetaIndex, uint32& Flags, uint32& BuildId, FString& BetaName, FString& Description);
	// bool SetActiveBeta(const FString& BetaName);

	/** UNTESTED */
	/**
	 * Gets the current language that the user has set.
	 *
	 * This falls back to the Steam UI language if the user hasn't explicitly picked a language for the title.
	 * 
	 * For the full list of languages see Supported Languages on Steamworks docs.
	 * @return The language.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static FString GetCurrentGameLanguage();

	/** UNTESTED */
	/**
	 * Gets the number of DLC pieces for the current app.
	 *
	 * This is typically used to loop through each piece of DLC and get the info about each one with BGetDLCDataByIndex.
	 * 
	 * @return The number of DLC pieces for the current app.
	 * Note that this value may max out at 64, depending on how much unowned DLC the user has.
	 * If your app has a large number of DLC, you should set your own internal list of known DLC to check against.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps", DisplayName="Get DLC Count")
	static int32 GetDLCCount();

	/** UNTESTED */
	/**
	 * Gets the download progress for optional DLC.
	 * 
	 * @param AppId The App ID of the DLC to monitor
	 * @param BytesDownloaded Returns the number of bytes downloaded.
	 * @param BytesTotal Returns the total size of the download in bytes.
	 * @return true if the specified DLC exists and is currently downloading; otherwise, false.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps", DisplayName="Get DLC Download Progress")
	static bool GetDLCDownloadProgress(const FAppId& AppId, FUInt64& BytesDownloaded, FUInt64& BytesTotal);

	/** UNTESTED */
	/**
	 * Gets the time of purchase of the specified app in Unix epoch format (time since Jan 1st, 1970).
	 *
	 * This is useful for rewarding users based on their initial purchase date.
	 * 
	 * @param AppId The App ID to get the purchase time for.
	 * @return The earliest purchase time in Unix epoch format (seconds since Jan 1st, 1970).
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static FDateTime GetEarliestPurchaseUnixTime(const FAppId& AppId);

	/** UNTESTED */
	// Implemented in an AsyncAction.
	// uint64 GetFileDetails(const FString& Filename);

	/** UNTESTED */
	/**
	 * Gets a list of all installed depots for a given App ID in mount order.
	 *
	 * @param AppId The App to list the depots for.
	 * @param MaxDepots The maximum number of depots to obtain, typically the size of pvecDepots.
	 * @return The array with all the depots ids installed.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static TArray<FDepotId> GetInstalledDepots(const FAppId& AppId, const int64 MaxDepots);

	/** UNTESTED */
	/**
	 * Gets the command line if the game was launched via Steam URL, e.g. steam://run/<appid>//<command line>/.
	 * This method is preferable to launching with a command line via the operating system, which can be a security risk.
	 * In order for rich presence joins to go through this and not be placed on the OS command line,
	 * you must enable "Use launch command line" from the Installation > General page on your app.
	 * 
	 * @param MaxExpectedLength Maximum length of the expected Name, used to reserve memory for the string.
	 * @return Returns the command line as a string.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps", meta=(AdvancedDisplay="MaxExpectedLength"))
	static FString GetLaunchCommandLine(int32 MaxExpectedLength = 128);

	/** UNTESTED */
	/**
	 * Gets the associated launch parameter if the game is run via steam://run/<appid>/?param1=value1;param2=value2;param3=value3 etc.
	 *
	 * Parameter names starting with the character '@' are reserved for internal use and will always return an empty string.
	 * Parameter names starting with an underscore '_' are reserved for steam features -- they can be queried by the game,
	 * but it is advised that you not param names beginning with an underscore for your own features.
	 * 
	 * @param Key The launch key to test for. Ex: param1
	 * @return The value associated with the key provided. Returns an empty string ("") if the specified key does not exist.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static FString GetLaunchQueryParam(const FString& Key);

	/** UNTESTED */
	// Install control for optional DLC

	/** UNTESTED */
	/**
	 * Allows you to install an optional DLC.
	 * 
	 * @param AppId The DLC you want to install.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static void InstallDLC(const FAppId& AppId);

	/** UNTESTED */
	/**
	 * Allows you to force verify game content on next launch.
	 *
	 * If you detect the game is out-of-date (for example, by having the client detect a version mismatch with a server),
	 * you can call use MarkContentCorrupt to force a verify, show a message to the user, and then quit.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static bool MarkContentCorrupt(const bool bMissingFilesOnly);

	// Obsolete
	// void RequestAllProofOfPurchaseKeys();

	/** UNTESTED */
	/**
	 * Allows you to uninstall an optional DLC.
	 * 
	 * @param AppId The DLC you want to uninstall.
	 */
	UFUNCTION(BlueprintCallable, Category="SteamDome|SteamApps")
	static void UninstallDLC(const FAppId& AppId);
};
