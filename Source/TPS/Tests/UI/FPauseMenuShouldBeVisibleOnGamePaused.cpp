﻿#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(PauseMenuShouldBeVisibleOnGamePaused, "TPS.UI.PauseMenuShouldBeVisibleOnGamePaused", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool PauseMenuShouldBeVisibleOnGamePaused::RunTest(const FString& Parameters)
{
    // Make the test pass by returning true, or fail by returning false.
    return true;
}
