#pragma once

#include "Tests/Utils/Controller/InputComponentHelper.h"
#include "Misc/AutomationTest.h"
#include "GameFramework/PlayerController.h"
#include "TPS/Tests/TestUtils.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FGameCanBePaused, "TPS.Controller.GameCanBePaused", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

using namespace TPS::Test;
using namespace Tests::InputComponentHelper;

bool FGameCanBePaused::RunTest(const FString& Parameters)
{
    const auto Level = LevelScope("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");  // [UnrealEd.SimpleMap] SimpleMapName
    APlayerController* PC = GetTestGameWorld()->GetFirstPlayerController();
    TestTrueExpr(PC != nullptr);
    TestTrueExpr(!PC->IsPaused());
    TestTrueExpr(!PC->bShowMouseCursor);
    PausePressed(PC->InputComponent);
    TestTrueExpr(PC->IsPaused());
    TestTrueExpr(PC->bShowMouseCursor);
    // Make the test pass by returning true, or fail by returning false.
    return true;
}
