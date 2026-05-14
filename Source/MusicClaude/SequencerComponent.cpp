#include "SequencerComponent.h"
#include "TimerManager.h"

USequencerComponent::USequencerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USequencerComponent::StartSequencer(USequencerData* InData)
{
    if (!InData) return;
    SequencerData = InData;
    RestartTimer();
}

void USequencerComponent::ResetPlayback()
{
    if (!SequencerData) return;
    RestartTimer();
}

void USequencerComponent::RestartTimer()
{
    CurrentStep = USequencerData::NumSteps - 1; // Prime so first AdvanceStep wraps to 0
    GetWorld()->GetTimerManager().ClearTimer(StepTimerHandle);
    GetWorld()->GetTimerManager().SetTimer(
        StepTimerHandle,
        this,
        &USequencerComponent::AdvanceStep,
        SequencerData->GetStepIntervalSeconds(),
        true
    );
}

void USequencerComponent::AdvanceStep()
{
    if (!SequencerData) return;

    CurrentStep = (CurrentStep + 1) % USequencerData::NumSteps;

    OnStepAdvanced.Broadcast(CurrentStep);

    for (int32 Row = 0; Row < USequencerData::NumRows; Row++)
    {
        if (SequencerData->GetStep(Row, CurrentStep))
        {
            OnStepTriggered.Broadcast(Row, CurrentStep);
        }
    }
}
