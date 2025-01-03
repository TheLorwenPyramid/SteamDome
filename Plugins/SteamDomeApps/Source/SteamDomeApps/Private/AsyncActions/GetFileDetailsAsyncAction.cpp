// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/GetFileDetailsAsyncAction.h"

#include <steam/isteamapps.h>

#include "Structs/FileDetailsResult.h"


UGetFileDetailsAsyncAction* UGetFileDetailsAsyncAction::GetFileDetails(
	const UObject* WorldContextObject, const FString& Filename
) {
	auto* Instance = NewObject<UGetFileDetailsAsyncAction>();
	Instance->WorldContext = WorldContextObject;
	Instance->Filename = Filename;
	Instance->SteamCallResult.Init(
		FOnFileDetailsReadyDelegate::CreateUObject(Instance, &UGetFileDetailsAsyncAction::OnGetFileDetails)
	);

	Instance->RegisterWithGameInstance(WorldContextObject);

	return Instance;
}


void UGetFileDetailsAsyncAction::Activate()
{
	Super::Activate();

	const SteamAPICall_t ApiCallId = SteamApps()->GetFileDetails(TCHAR_TO_UTF8(*Filename));
	SteamCallResult.Bind(ApiCallId);
}


void UGetFileDetailsAsyncAction::OnGetFileDetails(FileDetailsResult_t* FileDetailsResult, bool bIOFailure)
{
	if (!FileDetailsResult)
	{
		OnCompleted.Broadcast(false, FFileDetailsResult());
		
		SetReadyToDestroy();
		return;
	}

	const bool bSuccess = FileDetailsResult->m_eResult == k_EResultOK && !bIOFailure;
	OnCompleted.Broadcast(bSuccess, FFileDetailsResult(*FileDetailsResult));
		
	SetReadyToDestroy();
}
