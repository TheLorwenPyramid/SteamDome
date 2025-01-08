
#include "BlueprintLibraries/DepotIdFunctionLibrary.h"


FString UDepotIdFunctionLibrary::ToString(const FDepotId DepotId)
{
	return FString::Printf(TEXT("%u"), DepotId.DepotId);
}
