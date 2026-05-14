#include "ResetButtonWidget.h"
#include "MusicClaude.h"

void UResetButtonWidget::ResetSequencer()
{
    if (IsValid(SequencerComponent))
    {
        SequencerComponent->ResetPlayback();
    }
    else
    {
        UE_LOG(LogMusicClaude, Warning, TEXT("ResetButtonWidget: SequencerComponent not set"))
    }
}
