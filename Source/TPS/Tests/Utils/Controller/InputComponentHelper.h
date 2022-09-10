#pragma once
#include "Tests/TestUtils.h"

namespace Tests
{
namespace InputComponentHelper
{
    inline void PausePressed(UInputComponent* InputComponent)
    {
        const int32 ActionIndex = TPS::Test::GetActionBindingIndexByName(InputComponent, "ToggleGamePause", EInputEvent::IE_Pressed);
        if (ActionIndex != INDEX_NONE)
        {
            const auto JumpActionBind = InputComponent->GetActionBinding(ActionIndex);
            JumpActionBind.ActionDelegate.Execute(EKeys::P);
        }
    }
}
}