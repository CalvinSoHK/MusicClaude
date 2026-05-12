#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "Rendering/DrawElements.h"
#include "SequencerWidget.generated.h"

UCLASS()
class MUSICCLAUDE_API USequencerWidget : public UBaseWidget
{
    GENERATED_BODY()

public:
    static constexpr float CellWidth = 40.0f;
    static constexpr float CellHeight = 60.0f;

    virtual void InitWidget_Implementation(USequencerData* InData, USequencerComponent* InComponent) override;

    UFUNCTION(BlueprintCallable)
    void ToggleStep(int32 Row, int32 Step);

    UFUNCTION(BlueprintCallable)
    bool GetStep(int32 Row, int32 Step) const;

    UFUNCTION(BlueprintImplementableEvent)
    void OnStepFired(int32 Row, int32 Step);

protected:
    virtual void NativeConstruct() override;
    virtual int32 NativePaint(
        const FPaintArgs& Args,
        const FGeometry& AllottedGeometry,
        const FSlateRect& MyCullingRect,
        FSlateWindowElementList& OutDrawElements,
        int32 LayerId,
        const FWidgetStyle& InWidgetStyle,
        bool bParentEnabled) const override;
    virtual FReply NativeOnMouseButtonDown(
        const FGeometry& InGeometry,
        const FPointerEvent& InMouseEvent) override;
    virtual void NativeDestruct() override;

private:
    static const FLinearColor RowColors[USequencerData::NumRows];

    UFUNCTION()
    void HandleStepTriggered(int32 Row, int32 Step);

    UFUNCTION()
    void HandleStepAdvanced(int32 Step);
};
