#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SequencerData.generated.h"

UCLASS()
class MUSICCLAUDE_API USequencerData : public UObject
{
    GENERATED_BODY()

public:
    static constexpr int32 NumRows = 4;
    static constexpr int32 NumSteps = 32;

    UPROPERTY(BlueprintReadOnly)
    float BPM = 120.0f;

    UPROPERTY(BlueprintReadOnly)
    TArray<FString> InstrumentNames = { "Kick", "Snare", "HiHat", "Tom" };

    bool Grid[NumRows][NumSteps] = {};

    UFUNCTION(BlueprintCallable)
    void ToggleStep(int32 Row, int32 Step);

    UFUNCTION(BlueprintCallable)
    bool GetStep(int32 Row, int32 Step) const;

    float GetStepIntervalSeconds() const;
};
