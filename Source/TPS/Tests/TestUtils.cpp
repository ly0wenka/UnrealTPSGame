#if WITH_AUTOMATION_TESTS

#include "TPS/Tests/TestUtils.h"
#include "Misc/OutputDeviceNull.h"

namespace TPS
{
namespace Test
{
UWorld* GetTestGameWorld()
{
    const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
    for (const FWorldContext& Context : WorldContexts)
    {
        if ((Context.WorldType == EWorldType::PIE || Context.WorldType == EWorldType::Game) && Context.World())
        {
            return Context.World();
        }
    }

    return nullptr;
}

void CallFuncByNameWithParams(UObject* Object, const FString& FuncName, const TArray<FString>& Params)
{
    if (!Object) return;

    // Command pattern: "FunctionName Param1 Param2 Param3"
    FString Command = FuncName;
    for (const auto Param : Params)
    {
        Command.Append(" ").Append(Param);
    }
    FOutputDeviceNull OutputDeviceNull;
    Object->CallFunctionByNameWithArguments(*Command, OutputDeviceNull, nullptr, true);
}

FTPSUntilLatentCommand::FTPSUntilLatentCommand(TFunction<void()> InCallback, TFunction<void()> InTimeoutCallback, float InTimeout)
    : Callback(MoveTemp(InCallback)), TimeoutCallback(MoveTemp(InTimeoutCallback)), Timeout(InTimeout)
{
}

bool FTPSUntilLatentCommand::Update()
{
    const double NewTime = FPlatformTime::Seconds();
    if (NewTime - StartTime >= Timeout)
    {
        TimeoutCallback();
        return true;
    }

    Callback();
    return false;
}

int32 GetActionBindingIndexByName(UInputComponent* InputComp, const FString& ActionName, EInputEvent InputEvent)
{
    if (!InputComp) return INDEX_NONE;

    for (int32 i = 0; i < InputComp->GetNumActionBindings(); ++i)
    {
        const FInputActionBinding Action = InputComp->GetActionBinding(i);
        if (Action.GetActionName().ToString().Equals(ActionName) && Action.KeyEvent == InputEvent)
        {
            return i;
        }
    }

    return INDEX_NONE;
}

int32 GetAxisBindingIndexByName(UInputComponent* InputComp, const FString& AxisName)
{
    if (!InputComp) return INDEX_NONE;

    const int32 AxisIndex = InputComp->AxisBindings.IndexOfByPredicate(
        [=](const FInputAxisBinding& AxisBind) { return AxisBind.AxisName.ToString().Equals(AxisName); });

    return AxisIndex;
}

FString GetTestDataDir()
{
    return FPaths::GameSourceDir().Append("TPS/Tests/Data/");
}

FTakeScreenshotLatentCommand::FTakeScreenshotLatentCommand(const FString& InScreenshotName) : ScreenshotName(InScreenshotName)
{
    FAutomationTestFramework::Get().OnScreenshotTakenAndCompared.AddRaw(this, &FTakeScreenshotLatentCommand::OnScreenshotTakenAndCompared);
}

FTakeScreenshotLatentCommand::~FTakeScreenshotLatentCommand()
{
    FAutomationTestFramework::Get().OnScreenshotTakenAndCompared.RemoveAll(this);
}

void FTakeScreenshotLatentCommand::OnScreenshotTakenAndCompared()
{
    CommandCompleted = true;
}

FTakeGameScreenshotLatentCommand::FTakeGameScreenshotLatentCommand(const FString& InScreenshotName)
    : FTakeScreenshotLatentCommand(InScreenshotName)
{
}

bool FTakeGameScreenshotLatentCommand::Update()
{
    if (!ScreenshotRequested)
    {
        const auto Options = UAutomationBlueprintFunctionLibrary::GetDefaultScreenshotOptionsForRendering();
        UAutomationBlueprintFunctionLibrary::TakeAutomationScreenshotInternal(GetTestGameWorld(), ScreenshotName, FString{}, Options);
        ScreenshotRequested = true;
    }
    return CommandCompleted;
}

FTakeUIScreenshotLatentCommand::FTakeUIScreenshotLatentCommand(const FString& InScreenshotName)
    : FTakeScreenshotLatentCommand(InScreenshotName)
{
}

bool FTakeUIScreenshotLatentCommand::Update()
{
    if (!ScreenshotSetupDone)
    {
        ScreenshotSetupDone = true;
        SetBufferVisualization("Opacity");
        return false;
    }

    if (!ScreenshotRequested)
    {
        const auto Options = UAutomationBlueprintFunctionLibrary::GetDefaultScreenshotOptionsForRendering();
        UAutomationBlueprintFunctionLibrary::TakeAutomationScreenshotOfUI_Immediate(GetTestGameWorld(), ScreenshotName, Options);
        ScreenshotRequested = true;
    }
    return CommandCompleted;
}

void FTakeUIScreenshotLatentCommand::OnScreenshotTakenAndCompared()
{
    FTakeScreenshotLatentCommand::OnScreenshotTakenAndCompared();
    SetBufferVisualization(NAME_None);
}

void FTakeUIScreenshotLatentCommand::SetBufferVisualization(const FName& VisualizeBuffer)
{
    if (UGameViewportClient* ViewportClient = GEngine->GameViewport)
    {
        static IConsoleVariable* ICVar =
            IConsoleManager::Get().FindConsoleVariable(FBufferVisualizationData::GetVisualizationTargetConsoleCommandName());
        if (ICVar)
        {
            if (ViewportClient->GetEngineShowFlags())
            {
                ViewportClient->GetEngineShowFlags()->SetVisualizeBuffer(VisualizeBuffer == NAME_None ? false : true);
                ViewportClient->GetEngineShowFlags()->SetTonemapper(VisualizeBuffer == NAME_None ? true : false);
                ICVar->Set(VisualizeBuffer == NAME_None ? TEXT("") : *VisualizeBuffer.ToString());
            }
        }
    }
}

void SpecCloseLevel(UWorld* World)
{
    if (APlayerController* PC = World->GetFirstPlayerController())
    {
        PC->ConsoleCommand(TEXT("Exit"), true);
    }
}

}  // namespace Test
}  // namespace TPS

#endif