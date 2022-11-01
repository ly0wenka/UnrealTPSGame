#pragma once

#include "Tests/Utils/UI/WidgetBlueprintLibraryExtension.h"
#include "Misc/AutomationTest.h"
#include "Tests/TestUtils.h"
#include "Tests/Utils/Controller/InputComponentHelper.h"
#include "UI/PauseMenu/PauseMenuWidget.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPauseMenuShouldBeVisibleOnGamePaused, "TPS.UI.PauseMenuShouldBeVisibleOnGamePaused",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

using namespace TPS::Test;
using namespace Tests::InputComponentHelper;
using namespace Tests::WidgetBlueprintLibraryExtension;

bool FPauseMenuShouldBeVisibleOnGamePaused::RunTest(const FString& Parameters)
{
    const auto Level = LevelScope("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");  // [UnrealEd.SimpleMap] SimpleMapName
    const APlayerController* PC = GetTestGameWorld()->GetFirstPlayerController();
    TestTrueExpr(PC != nullptr);

    const UPauseMenuWidget* PauseMenuWidget = FindWidgetByClass<UPauseMenuWidget>();
    TestTrueExpr(PauseMenuWidget != nullptr);
    TestTrueExpr(PauseMenuWidget->GetVisibility() == ESlateVisibility::Collapsed);
    PausePressed(PC->InputComponent);
    TestTrueExpr(PauseMenuWidget->GetVisibility() == ESlateVisibility::Visible);

    // Make the test pass by returning true, or fail by returning false.
    return true;
}
