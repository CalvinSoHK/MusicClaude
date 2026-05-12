#include "SequencerComponent.h"
#include "TimerManager.h"

USequencerComponent::USequencerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USequencerComponent::BeginPlay()
{
    Super::BeginPlay();
}

void USequencerComponent::StartSequencer(USequencerData* InData)
{
    SequencerData = InData;
    CurrentStep = USequencerData::NumSteps - 1;

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

    for (int32 Row = 0; Row < USequencerData::NumRows; Row++)
    {
        if (SequencerData->GetStep(Row, CurrentStep))
        {
            OnStepTriggered.Broadcast(Row, CurrentStep);
        }
    }
}
