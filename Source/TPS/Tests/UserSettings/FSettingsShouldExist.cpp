#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TPSGameUserSettingsTests, "TPS.TPS.Tests.UserSettings.TPSGameUserSettingsTests",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TPSGameUserSettingsTests::RunTest(const FString& Parameters)
{
    // Make the test pass by returning true, or fail by returning false.
    return true;
}
