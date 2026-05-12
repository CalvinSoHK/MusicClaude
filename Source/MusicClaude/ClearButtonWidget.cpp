#include "ClearButtonWidget.h"

void UClearButtonWidget::ClearSequencer()
{
    if (IsValid(SequencerData))
    {
        SequencerData->ClearGrid();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("UClearButtonWidget::ClearSequencer called before SequencerData was initialized."))
    }
}
