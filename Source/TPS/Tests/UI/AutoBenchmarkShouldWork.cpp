#include "Misc/AutomationTest.h"
#include "Settings/TPSGameSetting.h"
#include "Settings/TPSGameUserSettings.h"
#include "Tests/TestUtils.h"
#include "Tests/Utils/Controller/InputComponentHelper.h"
#include "Tests/Utils/UI/SettingOptionHelper.h"
#include "UI/PauseMenu/PauseMenuWidget.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(AutoBenchmarkShouldWork, "TPS.UI.AutoBenchmarkShouldWork",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

using namespace TPS::Test;
using namespace Tests::InputComponentHelper;
using namespace Tests::SettingOptionHelper;

bool AutoBenchmarkShouldWork::RunTest(const FString& Parameters)
{
    const auto Level = LevelScope("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap"); // [UnrealEd.SimpleMap] SimpleMapName
    const APlayerController* PC = GetTestGameWorld()->GetFirstPlayerController();
    TestTrueExpr(PC!=nullptr);
    PausePressed(PC->InputComponent);

    DoBenchmarkClick();

    TArray<int32> SavedSettingOptionValues;
    const auto& VideoSettings = UTPSGameUserSettings::Get()->GetVideoSettings();
    for (const auto& Setting : VideoSettings)
    {
        SavedSettingOptionValues.Add(Setting->GetCurrentOption().Value);
    }
    for (int i = 0; i < VideoSettings.Num(); ++i)
    {
        NextSettingsClick(i);
    }
    for (int i = 0; i < VideoSettings.Num(); ++i)
    {
        TestTrueExpr(SavedSettingOptionValues[i] != VideoSettings[i]->GetCurrentOption().Value);
    }

    DoBenchmarkClick();

    for (int i = 0; i < VideoSettings.Num(); ++i)
    {
        TestTrueExpr(SavedSettingOptionValues[i] == VideoSettings[i]->GetCurrentOption().Value);
    }
    return true;
}
