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

	Instance->RegisterWithGameInstance(WorldContextObject);

	return Instance;
}


void UGetFileDetailsAsyncAction::Activate()
{
	Super::Activate();

	GetFileDetailsInternal = MakeUnique<FGetFileDetailsInternal>();
	GetFileDetailsInternal->OnGetFileDetailsEvent.BindUObject(this, &ThisClass::OnGetFileDetails);

	GetFileDetailsInternal->GetFileDetails(Filename);
}


void UGetFileDetailsAsyncAction::SetReadyToDestroy()
{
	GetFileDetailsInternal.Reset();

	Super::SetReadyToDestroy();
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


void FGetFileDetailsInternal::GetFileDetails(const FString& Filename)
{
	const SteamAPICall_t ApiCallId = SteamApps()->GetFileDetails(TCHAR_TO_UTF8(*Filename));
	OnGetFileDetailsFinished.Set(ApiCallId, this, &FGetFileDetailsInternal::OnGetFileDetails);
}


void FGetFileDetailsInternal::OnGetFileDetails(FileDetailsResult_t* FileDetailsResult, bool bIOFailure)
{
	OnGetFileDetailsEvent.ExecuteIfBound(FileDetailsResult, bIOFailure);
}
