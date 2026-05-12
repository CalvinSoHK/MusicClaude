#include "SequencerWidget.h"
#include "Styling/CoreStyle.h"

const FLinearColor USequencerWidget::RowColors[USequencerData::NumRows] = {
    FLinearColor(0.8f, 0.1f, 0.1f),
    FLinearColor(0.1f, 0.3f, 0.9f),
    FLinearColor(0.9f, 0.8f, 0.1f),
    FLinearColor(0.1f, 0.7f, 0.2f),
};

void USequencerWidget::NativeConstruct()
{
    Super::NativeConstruct();
    SetIsFocusable(true);
}

void USequencerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    Invalidate(EInvalidateWidgetReason::Paint);
}

int32 USequencerWidget::NativePaint(
    const FPaintArgs& Args,
    const FGeometry& AllottedGeometry,
    const FSlateRect& MyCullingRect,
    FSlateWindowElementList& OutDrawElements,
    int32 LayerId,
    const FWidgetStyle& InWidgetStyle,
    bool bParentEnabled) const
{
    const FSlateBrush* WhiteBrush = FCoreStyle::Get().GetBrush("WhiteTexture");
    const int32 CurrentStep = SequencerComponent ? SequencerComponent->CurrentStep : 0;

    FSlateDrawElement::MakeBox(
        OutDrawElements, LayerId,
        AllottedGeometry.ToPaintGeometry(
            FVector2D::ZeroVector,
            FVector2D(CellWidth * USequencerData::NumSteps, CellHeight * USequencerData::NumRows)),
        WhiteBrush,
        ESlateDrawEffect::None,
        FLinearColor(0.05f, 0.05f, 0.05f)
    );

    for (int32 Row = 0; Row < USequencerData::NumRows; Row++)
    {
        for (int32 Step = 0; Step < USequencerData::NumSteps; Step++)
        {
            const float X = Step * CellWidth;
            const float Y = Row * CellHeight;
            const bool bActive = SequencerData && SequencerData->GetStep(Row, Step);
            const bool bIsPlayhead = (Step == CurrentStep);

            FLinearColor CellColor;
            if (bActive)
            {
                CellColor = RowColors[Row];
                if (bIsPlayhead)
                    CellColor = FLinearColor::LerpUsingHSV(CellColor, FLinearColor::White, 0.4f);
            }
            else if (bIsPlayhead)
            {
                CellColor = FLinearColor(0.25f, 0.25f, 0.25f);
            }
            else
            {
                CellColor = FLinearColor(0.12f, 0.12f, 0.12f);
            }

            FSlateDrawElement::MakeBox(
                OutDrawElements, LayerId + 1,
                AllottedGeometry.ToPaintGeometry(FVector2D(X + 1.0f, Y + 1.0f), FVector2D(CellWidth - 2.0f, CellHeight - 2.0f)),
                WhiteBrush,
                ESlateDrawEffect::None,
                CellColor
            );
        }
    }

    const float PlayheadX = CurrentStep * CellWidth + CellWidth * 0.5f;
    TArray<FVector2f> LinePoints = {
        FVector2f(PlayheadX, 0.0f),
        FVector2f(PlayheadX, CellHeight * USequencerData::NumRows)
    };

    FSlateDrawElement::MakeLines(
        OutDrawElements, LayerId + 2,
        AllottedGeometry.ToPaintGeometry(),
        LinePoints,
        ESlateDrawEffect::None,
        FLinearColor::White,
        true,
        2.0f
    );

    return LayerId + 2;
}

FReply USequencerWidget::NativeOnMouseButtonDown(
    const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    const FVector2D LocalPos = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
    const int32 Col = FMath::FloorToInt(LocalPos.X / CellWidth);
    const int32 Row = FMath::FloorToInt(LocalPos.Y / CellHeight);

    if (Col >= 0 && Col < USequencerData::NumSteps && Row >= 0 && Row < USequencerData::NumRows)
    {
        ToggleStep(Row, Col);
    }

    return FReply::Handled();
}

void USequencerWidget::InitWidget(USequencerData* InData, USequencerComponent* InComponent)
{
    SequencerData = InData;
    SequencerComponent = InComponent;
    SequencerComponent->OnStepTriggered.AddDynamic(this, &USequencerWidget::HandleStepTriggered);
}

void USequencerWidget::ToggleStep(int32 Row, int32 Step)
{
    if (SequencerData)
    {
        SequencerData->ToggleStep(Row, Step);
    }
}

bool USequencerWidget::GetStep(int32 Row, int32 Step) const
{
    if (SequencerData)
    {
        return SequencerData->GetStep(Row, Step);
    }
    return false;
}

void USequencerWidget::HandleStepTriggered(int32 Row, int32 Step)
{
    OnStepFired(Row, Step);
}

void USequencerWidget::NativeDestruct()
{
    if (SequencerComponent)
    {
        SequencerComponent->OnStepTriggered.RemoveDynamic(this, &USequencerWidget::HandleStepTriggered);
    }
    Super::NativeDestruct();
}
