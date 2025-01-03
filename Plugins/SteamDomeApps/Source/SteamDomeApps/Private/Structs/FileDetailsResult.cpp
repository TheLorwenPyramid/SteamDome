#include "Structs/FileDetailsResult.h"

#include <steam/isteamapps.h>


FFileDetailsResult::FFileDetailsResult(const FileDetailsResult_t& Details)
	: Result(StaticCast<ESteamResult>(Details.m_eResult)),
	FileSize(Details.m_ulFileSize),
	FileSHA(FString(UTF8_TO_TCHAR(Details.m_FileSHA))),
	Flags(Details.m_unFlags)
{
	
}
