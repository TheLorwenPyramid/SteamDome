#pragma once


/**
 * Helper struct to automatically manage small buffers to be used in the Steamworks API calls.
 */
struct FTempString
{
protected:
	
	char* Buffer;

public:
	
	FTempString(const uint32 ReservedSize)
		: Buffer(new char[ReservedSize])
		{}

	~FTempString()
	{
		if (Buffer != nullptr)
		{
			delete Buffer;
			Buffer = nullptr;
		}
	}

	char* Start() const
	{
		return Buffer;
	}


	FString ToString() const
	{
		return FString(UTF8_TO_TCHAR(Buffer));
	}
};
