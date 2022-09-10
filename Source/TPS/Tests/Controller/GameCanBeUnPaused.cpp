#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(GameCanBeUnPaused, "TPS.TPS.Tests.Controller.GameCanBeUnPaused",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool GameCanBeUnPaused::RunTest(const FString& Parameters)
{
    // Make the test pass by returning true, or fail by returning false.
    return true;
}
