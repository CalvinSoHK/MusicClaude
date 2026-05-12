#include "ClearButtonWidget.h"

void UClearButtonWidget::ClearSequencer()
{
    if (IsValid(SequencerData))
    {
        SequencerData->ClearGrid();
    }
}
