#pragma once

#include "CoreMinimal.h"
#include "SteamActivateGameOverlayToWebPageMode.generated.h"


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
