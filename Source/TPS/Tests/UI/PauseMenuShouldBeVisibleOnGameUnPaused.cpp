#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(PauseMenuShouldBeVisibleOnGameUnPaused, "TPS.TPS.Tests.UI.PauseMenuShouldBeVisibleOnGameUnPaused",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool PauseMenuShouldBeVisibleOnGameUnPaused::RunTest(const FString& Parameters)
{
    // Make the test pass by returning true, or fail by returning false.
    return true;
}
