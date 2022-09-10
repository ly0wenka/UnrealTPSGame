#pragma once
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Tests/TestUtils.h"

namespace Tests
{
namespace WidgetBlueprintLibraryExtension
{
using namespace TPS::Test;
template <class T>
T* FindWidgetByClass()
{
    TArray<UUserWidget*> Widgets;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetTestGameWorld(), Widgets, T::StaticClass(), false);
    return Widgets.Num() != 0 ? Cast<T>(Widgets[0]) : nullptr;
}
}

}
