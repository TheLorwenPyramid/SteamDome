#include "steam/isteamfriends.h"
#if WITH_AUTOMATION_TESTS
 
#include "Misc/AutomationTest.h"
#include "Enums/SteamFriendFlags.h"
 
BEGIN_DEFINE_SPEC(FSteamFriendFlagsSpec, "SteamFriendFlags",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter);
END_DEFINE_SPEC(FSteamFriendFlagsSpec);
 
void FSteamFriendFlagsSpec::Define()
{
	Describe("ConvertSteamFriendFlagsToBitfield", [this]()
	{
		It("Should return only None when bitfield is 0", [this]()
		{
			const TSet Restrictions = { ESteamFriendFlags::None };
			const int32 Bitfield = ESteamFriendFlagsHelper::ConvertSteamFriendFlagsSetToBitfield(Restrictions);
			
			TestTrue("Is 0", Bitfield == 0);
		});

		It("Should return Steam's All when the All flag is enabled", [this]()
		{
			const TSet FriendFlags = { ESteamFriendFlags::All };
			const int32 Bitfield = ESteamFriendFlagsHelper::ConvertSteamFriendFlagsSetToBitfield(FriendFlags);
					
			TestTrue("Is All", Bitfield == EFriendFlags::k_EFriendFlagAll);
		});

		It("Should return valid value when mixing multiple flags", [this]()
		{
			const TSet FriendFlags = { ESteamFriendFlags::Ignored, ESteamFriendFlags::ChatMember };
			const int32 Bitfield = ESteamFriendFlagsHelper::ConvertSteamFriendFlagsSetToBitfield(FriendFlags);

			const int32 ExpectedBitfield = StaticCast<int32>(EFriendFlags::k_EFriendFlagIgnored) | StaticCast<int32>(EFriendFlags::k_EFriendFlagChatMember);

			TestTrue("Is valid", Bitfield == ExpectedBitfield);
		});
	});
}
 
#endif