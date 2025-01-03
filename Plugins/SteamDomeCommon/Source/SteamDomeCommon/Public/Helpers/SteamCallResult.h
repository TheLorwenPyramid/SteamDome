#pragma once

#include <steam/steam_api_common.h>

#define STEAMDOME_CALLRESULT(NAME, T) \
	using NAME = FSteamCallResult<T>; \
	using NAME##Delegate = FSteamCallResult<T>::FOnReadySignature;


/**
 * Transforms Steam's CallResults to Unreal's Delegates.
 *
 * # Using the macro:
 * To use I recommend using the STEAMDOME_CALLRESULT macro that works like so:
 * 
 * @code 
 * // In your class header declare:
 * STEAMDOME_CALLRESULT(FSomeTypeName, SteamType_t)
 * FSomeTypeName SomeTypeNameEvent;
 * @endcode
 *
 * In your implementation you can bind to the type using:
 * (FSomeTypeNameDelegate is automatically declared by the macro)
 * 
 * @code
 * FSomeTypeName.Bind(
 *		ApiCallId,
 *		FSomeTypeNameDelegate::CreateUObject(this, &YOURCLASS::YourMethod)
 * );
 * @endcode
 *
 * Where your method should have as parameters:
 * - The SteamType_t* that has the data requested.
 * - A boolean that indicates if it was an IO Failure. 
 * 
 * @tparam TEvent Steam type to be used.
 */
template<typename TEvent>
struct FSteamCallResult
{
protected:

	CCallResult<FSteamCallResult, TEvent> SteamCallback;

public:

	DECLARE_DELEGATE_TwoParams(FOnReadySignature, TEvent* /* SteamType */, bool /* bIOFailure */);

	TOptional<FOnReadySignature> OnReady;

	void Init(FOnReadySignature OnReadyCallback)
	{
		OnReady = TOptional{ OnReadyCallback };
	}

	void Bind(const SteamAPICall_t SteamAPICall)
	{
		checkf(OnReady.IsSet(), TEXT("Missing call to FSteamCallResult::Init before FSteamCallResult::Bind execution"));
		SteamCallback.Set(SteamAPICall, this, &FSteamCallResult::OnCompleted);
	}

protected:

	void OnCompleted(TEvent* Event, bool bIOFailure)
	{
		OnReady->ExecuteIfBound(Event, bIOFailure);
	}
};
