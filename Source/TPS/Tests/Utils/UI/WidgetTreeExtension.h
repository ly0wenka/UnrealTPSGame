#pragma once
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Widget.h"

namespace Tests
{
namespace WidgetTreeExtension
{
    inline UWidget* FindWidgetByName(const UUserWidget* Widget, const FName& WidgetName)
    {
        if (!Widget || !Widget->WidgetTree) return nullptr;
        UWidget* FoundedWidget = nullptr;
        UWidgetTree::ForWidgetAndChildren(Widget->WidgetTree->RootWidget,
            [&](UWidget* Child)
        {
            if (Child && Child->GetFName().IsEqual(WidgetName))
            {
                FoundedWidget = Child;
            }
        });
        return FoundedWidget;
    }
}
}
