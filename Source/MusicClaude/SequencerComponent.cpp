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
    CurrentStep = 0;

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

    for (int32 Row = 0; Row < USequencerData::NumRows; Row++)
    {
        if (SequencerData->GetStep(Row, CurrentStep))
        {
            OnStepTriggered.Broadcast(Row, CurrentStep);
        }
    }

    CurrentStep = (CurrentStep + 1) % USequencerData::NumSteps;
}
