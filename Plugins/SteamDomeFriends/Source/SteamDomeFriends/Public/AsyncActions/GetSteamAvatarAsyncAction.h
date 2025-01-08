// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/SteamId.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GetSteamAvatarAsyncAction.generated.h"


class USteamDomeFriendsSubsystem;


/**
 * The sizes of the Steam avatar to load.
 */
UENUM(BlueprintType)
enum class ESteamAvatarSize : uint8
{
	Small,	// 32x32 pixels
	Medium, // 64x64 pixels
	Large,	// 128x128 pixels
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadAvatarFinishSignature, UTexture2D*, Avatar);

/**
 * 
 */
UCLASS()
class STEAMDOMEFRIENDS_API UGetSteamAvatarAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<const UObject> WorldContext;

	UPROPERTY()
	FSteamId UserSteamId;

	UPROPERTY()
	ESteamAvatarSize Size;

	/* Common between the two types of async loading (they can't happen at the same time) */
	FDelegateHandle DelegateHandle;
	
	TObjectPtr<USteamDomeFriendsSubsystem> SteamDomeFriends;

public:

	UPROPERTY(BlueprintAssignable)
	FLoadAvatarFinishSignature OnFinish;
	
	/**
	 * Retrieves or requests the avatar image for a given SteamId user.
	 *
	 * If the image could not be retrieved, returns an invalid Texture2D.
	 *
	 * @note Requesting the large size, could mean waiting more for the image,
	 *		 as large avatars are not automatically downloaded by Steam.
	 * 
	 * @param WorldContextObject 
	 * @param SteamId SteamId for the user.
	 * @param AvatarSize The size of the requested image.
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", WorldContext="WorldContextObject"))
	static UGetSteamAvatarAsyncAction* GetSteamAvatar(
		const UObject* WorldContextObject, const FSteamId SteamId, const ESteamAvatarSize AvatarSize
	);

	virtual void Activate() override;

	/**
	 * TODO: Move to the SteamUtils when available.
	 * Returns an Texture2D containing the SteamId avatar if the PictureId is valid.
	 *
	 * @param PictureId 
	 * @param Width Optional, if not set, the PictureId width is retrieved from Steamworks API
	 * @param Height Optional, if not set, the PictureId height is retrieved from Steamworks API
	 * @return Texture2D containing the SteamId avatar if the PictureId is valid, nullptr otherwise 
	 */
	static UTexture2D* GetAvatarFromSteamCache(const int32 PictureId, uint32 Width, uint32 Height);
	static UTexture2D* GetAvatarFromSteamCache(const int32 PictureId);

protected:

	UFUNCTION()
	void OnPersonaStateChange(const FSteamId SteamId, const int32 PersonaFlags);

	UFUNCTION()
	void OnImageLoaded(const FSteamId SteamId, const int32 PictureId, const int32 Width, const int32 Height);

	int32 TryGetLoadedAvatarPictureIndex();

	void BroadcastAvatar(UTexture2D* Texture);
	void StopWithError();
};
