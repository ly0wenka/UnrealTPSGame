#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TPSTypes.generated.h"

UENUM(BlueprintType)
enum class EInventoryItemType : uint8
{
    SPHERE = 0 UMETA(DisplayName = "MY COOL SPHERE"),
    CUBE UMETA(DisplayName = "MY COOL CUBE"),
    CYLINDER,
    CONE
};

struct FInventoryItemInfo final
{
    EInventoryItemType Type;

    FInventoryItemInfo(const EInventoryItemType InType, const FString& InNamespace, const FString& InKey, const FString& InTextLiteral)
        : Type(InType),
          Namespace(InNamespace),
          Key(InKey),
          TextLiteral(InTextLiteral)
    {
    }

    FString Namespace;
    FString Key;
    FString TextLiteral;
};

const TArray InternationalizationArray = {
    FInventoryItemInfo(EInventoryItemType::SPHERE, "Inventory", "Sphere_Loc", "SPHERE"),
    FInventoryItemInfo(EInventoryItemType::CUBE, "Inventory", "Cube_Loc", "CUBE"),
    FInventoryItemInfo(EInventoryItemType::CYLINDER, "Inventory", "Cylinder_Loc", "CYLINDER"),
    FInventoryItemInfo(EInventoryItemType::CONE, "Inventory", "Cone_Loc", "CONE"),
};

UCLASS()
class UTPSLocalizationFuncLib : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure)
    static FText GetInventoryItemText(const EInventoryItemType InventoryItemType)
    {
        const FInventoryItemInfo* ItemInfo = InternationalizationArray.FindByPredicate([&, InventoryItemType](FInventoryItemInfo Item)
        {
            return Item.Type == InventoryItemType;
        });
        return FInternationalization::ForUseOnlyByLocMacroAndGraphNodeTextLiterals_CreateText(*ItemInfo->TextLiteral, *ItemInfo->Namespace, *ItemInfo->Key); //return NSLOCTEXT("","","");
    }
};

USTRUCT(BlueprintType)
struct FInventoryData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EInventoryItemType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
    int32 Score;

    FString ToString() const { return FString::Printf(TEXT("(Type=%i,Score=%i)"), Type, Score); }
};

USTRUCT(BlueprintType)
struct FHealthData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0"))
    float MaxHealth{100.0f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.1"))
    float HealModifier{10.0f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.1", Units = "s"))
    float HealRate{0.5f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.1", Units = "s"))
    float LifeSpan{5.0f};

    FString ToString() const
    {                                                                                           //
        return FString::Printf(TEXT("(MaxHealth=%f,HealModifier=%f,HealRate=%f,LifeSpan=%f)"),  //
            MaxHealth,                                                                          //
            HealModifier,                                                                       //
            HealRate,                                                                           //
            LifeSpan                                                                            //
        );
    }
};
