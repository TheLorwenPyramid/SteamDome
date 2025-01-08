// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/GetSteamAvatarAsyncAction.h"

#include <steam/isteamutils.h>

#include "Enums/SteamPersonaChange.h"
#include "Subsystems/SteamDomeFriendsSubsystem.h"


UGetSteamAvatarAsyncAction* UGetSteamAvatarAsyncAction::GetSteamAvatar(
	const UObject* WorldContextObject, const FSteamId SteamId, const ESteamAvatarSize AvatarSize
) {
	auto* Instance = NewObject<UGetSteamAvatarAsyncAction>();
	Instance->WorldContext = WorldContextObject;
	Instance->UserSteamId = SteamId;
	Instance->Size = AvatarSize;

	Instance->RegisterWithGameInstance(WorldContextObject);

	return Instance;
}


void UGetSteamAvatarAsyncAction::Activate()
{
	Super::Activate();

	const int32 ImageIndex = TryGetLoadedAvatarPictureIndex();

	if (ImageIndex > 0)
	{
		// Image can be loaded normally
		auto* AvatarPicture = GetAvatarFromSteamCache(ImageIndex);
		BroadcastAvatar(AvatarPicture);
		return;
	}

	// Handle image not being ready in cache
	
	if (ImageIndex == 0)
	{
		// Avatar is not set, we need to manually request it
		SteamDomeFriends = USteamDomeFriendsSubsystem::Get(WorldContext);
		DelegateHandle = SteamDomeFriends->OnPersonaStateChange.AddUObject(this, &UGetSteamAvatarAsyncAction::OnPersonaStateChange);
		const bool bSuccess = SteamDomeFriends->RequestUserInformation(UserSteamId.GetCSteamID(), false);

		if (!bSuccess)
		{
			StopWithError();
		}
	}
	else
	{
		// Avatar is automatically requested by Steamworks,
		// we just need to wait for the OnAvatarLoaded_t
		SteamDomeFriends = USteamDomeFriendsSubsystem::Get(WorldContext);
		DelegateHandle = SteamDomeFriends->OnAvatarImageLoaded.AddUObject(this, &UGetSteamAvatarAsyncAction::OnImageLoaded);
	}
}


UTexture2D* UGetSteamAvatarAsyncAction::GetAvatarFromSteamCache(const int32 PictureId, uint32 Width, uint32 Height)
{
	bool bSuccess = SteamUtils()->GetImageSize(PictureId, &Width, &Height);
	
	if (!bSuccess)
	{
		return nullptr;
	}

	constexpr int32 NumChannels = 4; // 4 channels = RGBA
	TArray<uint8> AvatarRGBA = TArray<uint8>();
	AvatarRGBA.SetNumUninitialized(Width * Height * NumChannels);
	
	bSuccess = SteamUtils()->GetImageRGBA(
		PictureId, AvatarRGBA.GetData(), AvatarRGBA.Num()
	);
	
	if (!bSuccess)
	{
		return nullptr;
	}

	return UTexture2D::CreateTransient(Width, Height, PF_R8G8B8A8, NAME_None, AvatarRGBA);
}


UTexture2D* UGetSteamAvatarAsyncAction::GetAvatarFromSteamCache(const int32 PictureId)
{
	uint32 Width, Height;
	const bool bSuccess = SteamUtils()->GetImageSize(PictureId, &Width, &Height);
		
	if (!bSuccess)
	{
		return nullptr;
	}

	return GetAvatarFromSteamCache(PictureId, Width, Height);
}


void UGetSteamAvatarAsyncAction::OnPersonaStateChange(const FSteamId SteamId, const int32 PersonaFlags)
{
	if (SteamId == UserSteamId && PersonaChange::HasBitEnabled(PersonaFlags, ESteamPersonaChange::Avatar))
	{
		SteamDomeFriends->OnPersonaStateChange.Remove(DelegateHandle);
		
		const int32 ImageIndex = TryGetLoadedAvatarPictureIndex();
		if (ImageIndex <= 0)
		{
			StopWithError();
			return;
		}

		auto* AvatarPicture = GetAvatarFromSteamCache(ImageIndex);
		BroadcastAvatar(AvatarPicture);
	}
}


void UGetSteamAvatarAsyncAction::OnImageLoaded(
	const FSteamId SteamId, const int32 PictureId, const int32 Width, const int32 Height
) {
	if (SteamId == UserSteamId)
	{
		SteamDomeFriends->OnAvatarImageLoaded.Remove(DelegateHandle);
		
		auto* AvatarPicture = GetAvatarFromSteamCache(PictureId, Width, Height);
		BroadcastAvatar(AvatarPicture);
	}
}


int32 UGetSteamAvatarAsyncAction::TryGetLoadedAvatarPictureIndex()
{
	switch (Size) {
	case ESteamAvatarSize::Small:
		return USteamDomeFriendsSubsystem::GetSmallFriendAvatar(UserSteamId);
	case ESteamAvatarSize::Medium:
		return USteamDomeFriendsSubsystem::GetMediumFriendAvatar(UserSteamId);
	case ESteamAvatarSize::Large:
		return USteamDomeFriendsSubsystem::GetLargeFriendAvatar(UserSteamId);
	}

	checkNoEntry();
	return -2;
}


void UGetSteamAvatarAsyncAction::BroadcastAvatar(UTexture2D* Texture)
{
	OnFinish.Broadcast(Texture);
	SetReadyToDestroy();
}


void UGetSteamAvatarAsyncAction::StopWithError()
{
	OnFinish.Broadcast(nullptr);
	SetReadyToDestroy();
}
