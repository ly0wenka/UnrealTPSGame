#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSettingsSholdBeApply, "TPS.UI.SettingsSholdBeApply",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FSettingsSholdBeApply::RunTest(const FString& Parameters)
{
    // Make the test pass by returning true, or fail by returning false.
    return true;
}
