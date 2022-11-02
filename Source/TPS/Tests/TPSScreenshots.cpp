// My game copyright

#if WITH_AUTOMATION_TESTS

#include "TPS/Tests/TPSScreenshots.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "TPS/Tests/TestUtils.h"
#include "AutomationBlueprintFunctionLibrary.h"
#include "TakeScreenshotAfterTimeLatentAction.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRenderingShouldBeCorrect, "TPSGame.Screenshots.RenderingShouldBeCorrect",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

using namespace TPS::Test;

class FTakeGameScreenshotLatentCommand: public IAutomationLatentCommand
{
public:
    FTakeGameScreenshotLatentCommand(const FString& InScreenshotName): ScreenshotName()
    {
        FAutomationTestFramework::Get().OnScreenshotTakenAndCompared.AddRaw(this, &FTakeGameScreenshotLatentCommand::OnScreenshotTakenAndCompared);

    }

    virtual ~FTakeGameScreenshotLatentCommand()
    {
        FAutomationTestFramework::Get().OnScreenshotTakenAndCompared.RemoveAll(this);
    }

    virtual bool Update() override
    {
        if (!ScreenshotRequested)
        {
            const auto Options = UAutomationBlueprintFunctionLibrary::GetDefaultScreenshotOptionsForRendering();
            const FString Notes{};
            UAutomationBlueprintFunctionLibrary::TakeAutomationScreenshotInternal(GetTestGameWorld(), ScreenshotName, Notes, Options);
            ScreenshotRequested = true;

            return CommandCompleted;
        }
        UE_LOG(LogTemp, Display, TEXT("Frame %i"), GFrameCounter);
        return CommandCompleted;
    }
private:
    const FString ScreenshotName;
    bool ScreenshotRequested{false};
    bool CommandCompleted{false};
    
    void OnScreenshotTakenAndCompared() { CommandCompleted = true; }
};

bool FRenderingShouldBeCorrect::RunTest(const FString& Parameters)
{
    const auto Level = LevelScope("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");  // [UnrealEd.SimpleMap] SimpleMapName
    ADD_LATENT_AUTOMATION_COMMAND(FTakeGameScreenshotLatentCommand("rendering_check_screenshot"));
    return true;
}

#endif
