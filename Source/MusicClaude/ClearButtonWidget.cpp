#include "ClearButtonWidget.h"
#include "MusicClaude.h"

void UClearButtonWidget::ClearSequencer()
{
    if (IsValid(SequencerData))
    {
        SequencerData->ClearGrid();
    }
    else
    {
        UE_LOG(LogMusicClaude, Warning, TEXT("ClearButtonWidget: SequencerData not set"))
    }
}
