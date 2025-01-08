#pragma once

#include "CoreMinimal.h"
#include <steam/isteamfriends.h>
#include "SteamActivateGameOverlayToWebPageMode.generated.h"


/**
 * Game Overlay web page modes
 */
UENUM(BlueprintType)
enum class ESteamActivateGameOverlayToWebPageMode : uint8
{
	/**
	 * Browser will open next to all other windows that the user has open in the overlay.
	 * The window will remain open, even if the user closes then re-opens the overlay.
	 */
	Default = 0,
	/**
	 * Browser will be opened in a special overlay configuration which hides all other windows that the user has open
	 * in the overlay. When the user closes the overlay, the browser window will also close.
	 * When the user closes the browser window, the overlay will automatically close.
	 */
	Modal = 1,
};


namespace SteamActivateGameOverlayToWebPageMode
{
	inline EActivateGameOverlayToWebPageMode STEAMDOMEFRIENDS_API ToSteamEnum(const ESteamActivateGameOverlayToWebPageMode SteamActivateGameOverlayToWebPageMode)
	{
		return StaticCast<EActivateGameOverlayToWebPageMode>(SteamActivateGameOverlayToWebPageMode);
	}

	inline ESteamActivateGameOverlayToWebPageMode STEAMDOMEFRIENDS_API FromSteamEnum(const EActivateGameOverlayToWebPageMode ActivateGameOverlayToWebPageMode)
	{
		return StaticCast<ESteamActivateGameOverlayToWebPageMode>(ActivateGameOverlayToWebPageMode);
	}
}
