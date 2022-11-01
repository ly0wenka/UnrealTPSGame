#pragma once
#include "WidgetBlueprintLibraryExtension.h"
#include "WidgetTreeExtension.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "UI/PauseMenu/SettingOptionWidget.h"
#include "UI/PauseMenu/VideoSettingsWidget.h"

namespace Tests
{
namespace SettingOptionHelper
{
using namespace WidgetBlueprintLibraryExtension;
using namespace WidgetTreeExtension;

inline const USettingOptionWidget* CreateSettingOptionWidget(int32 SettingsIndex)
{
    const UVideoSettingsWidget* VideoSettingsWidget = FindWidgetByClass<UVideoSettingsWidget>();
    const UVerticalBox* VerticalBox = Cast<UVerticalBox>(FindWidgetByName(VideoSettingsWidget, "VideoSettingsContainer"));
    return Cast<USettingOptionWidget>(VerticalBox->GetChildAt(SettingsIndex));
}

inline void Click(const UUserWidget* UserWidget, const char* WidgetName)
{
    const UButton* Button = Cast<UButton>(FindWidgetByName(UserWidget, WidgetName));
    Button->OnClicked.Broadcast();
}

inline void NextSettingsClick(int32 SettingsIndex)
{
    const USettingOptionWidget* SettingOptionWidget = CreateSettingOptionWidget(SettingsIndex);
    const char* WidgetName = "NextSettingButton";
    Click(SettingOptionWidget, WidgetName);
}

inline void PrevSettingsClick(int32 SettingsIndex)
{
    const USettingOptionWidget* SettingOptionWidget = CreateSettingOptionWidget(SettingsIndex);
    const char* WidgetName = "PrevSettingButton";
    Click(SettingOptionWidget, WidgetName);
}

inline void DoBenchmarkClick()
{
    const UVideoSettingsWidget* VideoSettingsWidget = FindWidgetByClass<UVideoSettingsWidget>();
    const char* WidgetName = "RunBenchmarkButton";
    Click(VideoSettingsWidget, WidgetName);
}
}  // namespace SettingOptionHelper
}  // namespace Tests
