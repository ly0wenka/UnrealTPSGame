#pragma once
#include "Tests/TestUtils.h"

namespace Tests
{
namespace InputComponentHelper
{
    inline void DoInputAction(UInputComponent* InputComponent, const FString& ActionName, const FKey& Key)
    {
        const int32 ActionIndex = TPS::Test::GetActionBindingIndexByName(InputComponent, ActionName, EInputEvent::IE_Pressed);
        if (ActionIndex != INDEX_NONE)
        {
            const auto ActionBind = InputComponent->GetActionBinding(ActionIndex);
            ActionBind.ActionDelegate.Execute(Key);
        }
    }

    inline void JumpPressed(UInputComponent* InputComponent)
    {
        DoInputAction(InputComponent, "Jump", EKeys::SpaceBar);
    }

    inline void PausePressed(UInputComponent* InputComponent)
    {
        DoInputAction(InputComponent, "ToggleGamePause", EKeys::P);
    }
}
}