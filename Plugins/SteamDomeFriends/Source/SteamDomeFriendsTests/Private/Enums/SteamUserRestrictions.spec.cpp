#if WITH_AUTOMATION_TESTS
 
#include "Misc/AutomationTest.h"
#include "Enums/SteamUserRestrictions.h"
 
BEGIN_DEFINE_SPEC(FSteamUserRestrictionsSpec, "SteamUserRestrictions",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter);
END_DEFINE_SPEC(FSteamUserRestrictionsSpec);
 
void FSteamUserRestrictionsSpec::Define()
{
	Describe("Convert Bitfield to Set<SteamUserRestriction>", [this]()
	{
		It("Should return only None when bitfield is 0", [this]()
		{
			constexpr int32 Bitfield = 0;
			const TSet<ESteamUserRestriction> Set = ConvertBitfieldToSteamUserRestrictions(Bitfield);
			
			TestTrue("Only contains one flag", Set.Num() == 1);
			TestTrue("Contains None", Set.Contains(ESteamUserRestriction::None));
		});

		It("Should convert correctly when two flags are enabled", [this]()
		{
			const int32 Bitfield = StaticCast<int32>(ESteamUserRestriction::Trading) | StaticCast<int32>(ESteamUserRestriction::GroupChat);
			
			const TSet<ESteamUserRestriction> Set = ConvertBitfieldToSteamUserRestrictions(Bitfield);
					
			TestTrue("Only contains two flags", Set.Num() == 2);
			TestTrue("Contains Trading", Set.Contains(ESteamUserRestriction::Trading));
			TestTrue("Contains GroupChat", Set.Contains(ESteamUserRestriction::GroupChat));
		});
	});

	Describe("Convert Set<SteamUserRestriction> to bitfield", [this]()
	{
		It("Should return 0 when Set has None", [this]()
		{
			const auto Restrictions = { ESteamUserRestriction::None };
			const int32 Bitfield = ConvertSteamUserRestrictionsToBitfield(Restrictions);

			TestTrue("Bitfield is 0", Bitfield == 0);
		});

		It("Should return valid when flags are set", [this]()
		{
			const auto Restrictions = {
				ESteamUserRestriction::Rating,
				ESteamUserRestriction::AnyChat,
			};
			
			const int32 Bitfield = ConvertSteamUserRestrictionsToBitfield(Restrictions);

			const int32 ExpectedBitfield = StaticCast<int32>(ESteamUserRestriction::Rating) | StaticCast<int32>(ESteamUserRestriction::AnyChat);
			TestTrue("Bitfield is valid", Bitfield == ExpectedBitfield);
		});
	});
}
 
#endif