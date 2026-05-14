#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SequencerData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGridCleared);

UCLASS(BlueprintType)
class MUSICCLAUDE_API USequencerData : public UObject
{
    GENERATED_BODY()

public:
    USequencerData();

    static constexpr int32 NumRows = 4;
    static constexpr int32 NumSteps = 32;

    // Fixed at 120 for now; runtime BPM change would require clearing and restarting the timer in USequencerComponent
    UPROPERTY(BlueprintReadOnly)
    float BPM = 120.0f;

    UPROPERTY()
    TArray<bool> Grid;

    UPROPERTY(BlueprintAssignable)
    FOnGridCleared OnGridCleared;

    UFUNCTION(BlueprintCallable)
    void ToggleStep(int32 Row, int32 Step);

    UFUNCTION(BlueprintCallable)
    bool GetStep(int32 Row, int32 Step) const;

    UFUNCTION(BlueprintCallable)
    void ClearGrid();

    UFUNCTION(BlueprintCallable)
    float GetStepIntervalSeconds() const;
};
