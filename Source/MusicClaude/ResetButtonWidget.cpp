#include "ResetButtonWidget.h"

void UResetButtonWidget::ResetSequencer()
{
    if (IsValid(SequencerComponent))
    {
        SequencerComponent->ResetPlayback();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("UResetButtonWidget::ResetSequencer called before SequencerComponent was initialized."))
    }
}
