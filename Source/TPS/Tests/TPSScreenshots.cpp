// My game copyright

#if WITH_AUTOMATION_TESTS

#include "TPS/Tests/TPSScreenshots.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "TPS/Tests/TestUtils.h"
#include "AutomationBlueprintFunctionLibrary.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRenderingShouldBeCorrect, "TPSGame.Screenshots.RenderingShouldBeCorrect",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

using namespace TPS::Test;

class FTakeGameScreenshotLatentCommand: public IAutomationLatentCommand
{
public:
    FTakeGameScreenshotLatentCommand(const FString& InScreenshotName): ScreenshotName()
    {
        
    }

    virtual ~FTakeGameScreenshotLatentCommand()
    {
        
    }

    virtual bool Update() override
    {
        return true;
    }
private:
    const FString ScreenshotName;
};

bool FRenderingShouldBeCorrect::RunTest(const FString& Parameters)
{
    const auto Level = LevelScope("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");  // [UnrealEd.SimpleMap] SimpleMapName
    ADD_LATENT_AUTOMATION_COMMAND(FTakeGameScreenshotLatentCommand("rendering_check_screenshot"));
    return true;
}

#endif
