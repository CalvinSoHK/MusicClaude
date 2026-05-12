#include "ResetButtonWidget.h"

void UResetButtonWidget::ResetSequencer()
{
    if (IsValid(SequencerComponent))
    {
        SequencerComponent->ResetPlayback();
    }
}
