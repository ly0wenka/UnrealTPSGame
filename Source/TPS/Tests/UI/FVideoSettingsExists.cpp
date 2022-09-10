#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVideoSettingsExists, "TPS.TPS.Tests.UI.FVideoSettingsExists",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FVideoSettingsExists::RunTest(const FString& Parameters)
{
    // Make the test pass by returning true, or fail by returning false.
    return true;
}
