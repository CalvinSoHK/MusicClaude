#include "SequencerData.h"

void USequencerData::ToggleStep(int32 Row, int32 Step)
{
    if (Row >= 0 && Row < NumRows && Step >= 0 && Step < NumSteps)
    {
        Grid[Row][Step] = !Grid[Row][Step];
    }
}

bool USequencerData::GetStep(int32 Row, int32 Step) const
{
    if (Row >= 0 && Row < NumRows && Step >= 0 && Step < NumSteps)
    {
        return Grid[Row][Step];
    }
    return false;
}

void USequencerData::ClearGrid()
{
    FMemory::Memzero(Grid, sizeof(Grid));
}

float USequencerData::GetStepIntervalSeconds() const
{
    // 8th note interval at current BPM
    return 60.0f / BPM / 2.0f;
}
