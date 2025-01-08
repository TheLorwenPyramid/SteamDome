#pragma once

#include "Structs/AppId.h"
#include "AppIdFunctionLibrary.generated.h"


UCLASS()
class STEAMDOMECORE_API UAppIdFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category="SteamDome|Common", meta=(DisplayName="Convert To String", CompactNodeTitle="->", BlueprintAutocast))
	static FString ToString(FAppId AppId);
};
