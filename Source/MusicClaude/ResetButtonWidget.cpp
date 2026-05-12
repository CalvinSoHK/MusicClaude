#include "ResetButtonWidget.h"

void UResetButtonWidget::ResetSequencer()
{
    if (SequencerComponent)
    {
        SequencerComponent->ResetPlayback();
    }
}
