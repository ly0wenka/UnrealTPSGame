#pragma once
#include "Tests/Utils/UI/SettingOptionHelper.h"
#include "Misc/AutomationTest.h"
#include "Settings/TPSGameSetting.h"
#include "Settings/TPSGameUserSettings.h"
#include "Tests/TestUtils.h"
#include "Tests/Utils/Controller/InputComponentHelper.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FSettingsCanBeApply, "TPS.UI.SettingsCanBeApply", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

using namespace TPS::Test;
using namespace Tests::InputComponentHelper;
using namespace Tests::SettingOptionHelper;

bool FSettingsCanBeApply::RunTest(const FString& Parameters)
{
    const auto Level = LevelScope("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");  // [UnrealEd.SimpleMap] SimpleMapName
    const APlayerController* PC = GetTestGameWorld()->GetFirstPlayerController();
    TestTrueExpr(PC != nullptr);
    PausePressed(PC->InputComponent);

    const auto& VideoSettings = UTPSGameUserSettings::Get()->GetVideoSettings();

    const int32 GIQualityBefore = UTPSGameUserSettings::Get()->GetGlobalIlluminationQuality();
    TestTrueExpr(GIQualityBefore == VideoSettings[2]->GetCurrentOption().Value);

    NextSettingsClick(2);

    const int32 GIQualityAfter = UTPSGameUserSettings::Get()->GetGlobalIlluminationQuality();
    TestTrueExpr(GIQualityBefore != GIQualityAfter);
    TestTrueExpr(GIQualityAfter == VideoSettings[2]->GetCurrentOption().Value);

    UTPSGameUserSettings::Get()->SetGlobalIlluminationQuality(GIQualityBefore);
    UTPSGameUserSettings::Get()->ApplySettings(false);
    // for (int32 i = 0; i < 5; ++i)
    // {
    //     ADD_LATENT_AUTOMATION_COMMAND(FWaitLatentCommand(1.0f));
    //     ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand(
    //         [&, i]()
    //         {
    //             DoSettingsClick(i);
    //             return  true;
    //         }));
    //     ADD_LATENT_AUTOMATION_COMMAND(FWaitLatentCommand(1.0f));
    // }
    return true;
}
