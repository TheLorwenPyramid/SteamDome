
#include "Enums/SteamUserRestrictions.h"


FORCEINLINE void IncludeIfBitIsSet(
	const ESteamUserRestriction Restriction, const int32 Flags, TSet<ESteamUserRestriction>& Set
) {
	if (Flags & StaticCast<int32>(Restriction))
	{
		Set.Add(Restriction);
	}
}

TSet<ESteamUserRestriction> ESteamUserRestrictionHelper::ConvertBitfieldToSteamUserRestrictions(const int32 Bitfield)
{
	TSet<ESteamUserRestriction> Restrictions;

	if (Bitfield == 0)
	{
		Restrictions.Add(ESteamUserRestriction::None);
		return Restrictions;
	}
	
	// IncludeIfBitIsSet(ESteamUserRestriction::None, Bitfield, Restrictions); -- Does nothing
	IncludeIfBitIsSet(ESteamUserRestriction::Unknown, Bitfield, Restrictions);
	IncludeIfBitIsSet(ESteamUserRestriction::AnyChat, Bitfield, Restrictions);
	IncludeIfBitIsSet(ESteamUserRestriction::VoiceChat, Bitfield, Restrictions);
	IncludeIfBitIsSet(ESteamUserRestriction::GroupChat, Bitfield, Restrictions);
	IncludeIfBitIsSet(ESteamUserRestriction::Rating, Bitfield, Restrictions);
	IncludeIfBitIsSet(ESteamUserRestriction::GameInvites, Bitfield, Restrictions);
	IncludeIfBitIsSet(ESteamUserRestriction::Trading, Bitfield, Restrictions);

	return Restrictions;
}


int32 ESteamUserRestrictionHelper::ConvertSteamUserRestrictionsToBitfield(const TSet<ESteamUserRestriction>& Set)
{
	int32 Bitflag = 0;
	
	for (const auto Value : Set)
	{
		Bitflag |= StaticCast<int32>(Value);
	}

	return Bitflag;
}
