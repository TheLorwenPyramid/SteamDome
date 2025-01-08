#include "BlueprintLibraries/AppIdFunctionLibrary.h"


FString UAppIdFunctionLibrary::ToString(FAppId AppId)
{
	return FString::Printf(TEXT("%u"), AppId.AppId);
}
