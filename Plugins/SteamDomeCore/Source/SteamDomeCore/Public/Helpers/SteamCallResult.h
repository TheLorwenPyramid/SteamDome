﻿#pragma once

#include <steam/steam_api_common.h>


#define STEAMDOME_CALLRESULT(NAME, T) \
	using NAME = TSteamCallResult<T>; \
	using NAME##Delegate = TSteamCallResult<T>::FCallResultDelegate;


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
struct TSteamCallResult
{
	using FCallResultDelegate = TDelegate<void(TEvent* /* SteamType */, bool /* bIOFailure */)>;

protected:

	CCallResult<TSteamCallResult, TEvent> SteamCallback;

	TOptional<FCallResultDelegate> OnReady;

public:
	
	/**
	 * Initialize Unreal's delegate with your own callback that indicates the method/function to be called.
	 *
	 * Only initialize the value once per instance of this struct.
	 */
	void Init(FCallResultDelegate OnReadyCallback)
	{
		OnReady = TOptional{ OnReadyCallback };
	}
	
	/**
	 * Bind the Steam CallResult to the delegate given in the Init method.
	 */
	bool Bind(const SteamAPICall_t SteamAPICall)
	{
		checkf(OnReady.IsSet(), TEXT("Missing call to FSteamCallResult::Init before FSteamCallResult::Bind execution"));

		if (SteamAPICall == k_uAPICallInvalid)
		{
			return false;
		}
		
		UE_LOG(LogTemp, Error, TEXT("Bound"));

		SteamCallback.Set(SteamAPICall, this, &TSteamCallResult::OnCompleted);
		return true;
	}

protected:

	void OnCompleted(TEvent* Event, bool bIOFailure)
	{
		UE_LOG(LogTemp, Error, TEXT("OnCompleted"));
		OnReady->ExecuteIfBound(Event, bIOFailure);
	}
};
