#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(AutoBenchmarkShouldWork, "TPS.TPS.Tests.UI.AutoBenchmarkShouldWork",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool AutoBenchmarkShouldWork::RunTest(const FString& Parameters)
{
    // Make the test pass by returning true, or fail by returning false.
    return true;
}
