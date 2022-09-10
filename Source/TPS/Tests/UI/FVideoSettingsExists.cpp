#pragma once
#include "Tests/Utils/UI/WidgetBlueprintLibraryExtension.h"
#include "Tests/Utils/UI/WidgetTreeExtension.h"
#include "Misc/AutomationTest.h"
#include "Tests/TestUtils.h"
#include "UI/PauseMenu/VideoSettingsWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Settings/TPSGameUserSettings.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVideoSettingsExists, "TPS.UI.FVideoSettingsExists",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

using namespace TPS::Test;
using namespace Tests::WidgetBlueprintLibraryExtension;
using namespace Tests::WidgetTreeExtension;

bool FVideoSettingsExists::RunTest(const FString& Parameters)
{
    const auto Level = LevelScope("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap"); // [UnrealEd.SimpleMap] SimpleMapName
    const UVideoSettingsWidget* VideoSettingsWidget = FindWidgetByClass<UVideoSettingsWidget>();
    TestTrueExpr(VideoSettingsWidget!=nullptr);

    const UButton* BenchmarkButton = Cast<UButton>(FindWidgetByName(VideoSettingsWidget, "RunBenchmarkButton"));
    TestTrueExpr(BenchmarkButton!=nullptr);

    const UVerticalBox* VerticalBox = Cast<UVerticalBox>(FindWidgetByName(VideoSettingsWidget, "VideoSettingsContainer"));
    TestTrueExpr(VerticalBox!=nullptr);

    const UTPSGameUserSettings* Settings = UTPSGameUserSettings::Get();
    TestTrueExpr(Settings!=nullptr);
    const auto& VideoSettings = Settings->GetVideoSettings();
    TestTrueExpr(VerticalBox->GetChildrenCount() == VideoSettings.Num());
    TestTrueExpr(VerticalBox->GetChildrenCount() > 0);
    // Make the test pass by returning true, or fail by returning false.
    return true;
}
