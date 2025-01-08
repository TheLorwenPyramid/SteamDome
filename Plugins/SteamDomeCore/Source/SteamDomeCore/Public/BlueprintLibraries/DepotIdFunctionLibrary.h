#pragma once

#include "Structs/DepotId.h"
#include "DepotIdFunctionLibrary.generated.h"


UCLASS()
class STEAMDOMECORE_API UDepotIdFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category="SteamDome|Common", meta=(DisplayName="Convert To String", CompactNodeTitle="->", BlueprintAutocast))
	static FString ToString(FDepotId DepotId);
};
