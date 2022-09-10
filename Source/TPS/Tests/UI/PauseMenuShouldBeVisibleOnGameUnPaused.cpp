#pragma once
#include "Tests/Utils/UI/WidgetBlueprintLibraryExtension.h"
#include "Misc/AutomationTest.h"
#include "Tests/TestUtils.h"
#include "Tests/Utils/Controller/InputComponentHelper.h"
#include "UI/PauseMenu/PauseMenuWidget.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(PauseMenuShouldBeVisibleOnGameUnPaused, "TPS.TPS.Tests.UI.PauseMenuShouldBeVisibleOnGameUnPaused",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

using namespace TPS::Test;
using namespace Tests::WidgetBlueprintLibraryExtension;
using namespace Tests::InputComponentHelper;

bool PauseMenuShouldBeVisibleOnGameUnPaused::RunTest(const FString& Parameters)
{
    const auto Level = LevelScope("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap"); // [UnrealEd.SimpleMap] SimpleMapName
    const APlayerController* PC = GetTestGameWorld()->GetFirstPlayerController();
    TestTrueExpr(PC!=nullptr);

    const UPauseMenuWidget* PauseMenuWidget = FindWidgetByClass<UPauseMenuWidget>();
    TestTrueExpr(PauseMenuWidget!=nullptr);
    TestTrueExpr(PauseMenuWidget->GetVisibility() == ESlateVisibility::Collapsed);
    
    PausePressed(PC->InputComponent);
    PausePressed(PC->InputComponent);

    TestTrueExpr(PauseMenuWidget->GetVisibility() == ESlateVisibility::Collapsed);
    return true;
}
