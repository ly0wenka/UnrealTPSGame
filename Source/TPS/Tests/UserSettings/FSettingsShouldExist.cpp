#pragma once
#include "Misc/AutomationTest.h"
#include "Settings/TPSGameUserSettings.h"
#include "Tests/TestUtils.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FSettingsShouldExist, "TPS.UserSettings.SettingsShouldExist", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

using namespace TPS::Test;

bool FSettingsShouldExist::RunTest(const FString& Parameters)
{
    const auto Level = LevelScope("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");  // [UnrealEd.SimpleMap] SimpleMapName

    TestTrueExpr(UTPSGameUserSettings::Get() != nullptr);
    TestTrueExpr(UTPSGameUserSettings::Get()->GetVideoSettings().Num() == 7);

    // Make the test pass by returning true, or fail by returning false.
    return true;
}
