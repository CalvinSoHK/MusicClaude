#include "SequencerData.h"

USequencerData::USequencerData()
{
    Grid.Init(false, NumRows * NumSteps);
}

void USequencerData::ToggleStep(int32 Row, int32 Step)
{
    if (Row >= 0 && Row < NumRows && Step >= 0 && Step < NumSteps)
    {
        Grid[Row * NumSteps + Step] = !Grid[Row * NumSteps + Step];
    }
}

bool USequencerData::GetStep(int32 Row, int32 Step) const
{
    if (Row >= 0 && Row < NumRows && Step >= 0 && Step < NumSteps)
    {
        return Grid[Row * NumSteps + Step];
    }
    return false;
}

void USequencerData::ClearGrid()
{
    Grid.Init(false, NumRows * NumSteps);
    OnGridCleared.Broadcast();
}

float USequencerData::GetStepIntervalSeconds() const
{
    // 32 steps = 4 bars at 8th-note resolution; halve the quarter-note interval for the grid subdivision
    return 60.0f / BPM / 2.0f;
}
