#pragma once
#include "Misc/AutomationTest.h"
#include "TPS/Tests/TestUtils.h"
#include "Tests/Utils/Controller/InputComponentHelper.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    GameCanBeUnPaused, "TPS.Controller.GameCanBeUnPaused", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

using namespace TPS::Test;
using namespace Tests::InputComponentHelper;

bool GameCanBeUnPaused::RunTest(const FString& Parameters)
{
    const auto Level = LevelScope("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");  // [UnrealEd.SimpleMap] SimpleMapName
    APlayerController* PC = GetTestGameWorld()->GetFirstPlayerController();
    TestTrueExpr(PC != nullptr);
    TestTrueExpr(!PC->IsPaused());
    TestTrueExpr(!PC->bShowMouseCursor);

    PausePressed(PC->InputComponent);
    PausePressed(PC->InputComponent);

    TestTrueExpr(!PC->IsPaused());
    TestTrueExpr(!PC->bShowMouseCursor);
    return true;
}
