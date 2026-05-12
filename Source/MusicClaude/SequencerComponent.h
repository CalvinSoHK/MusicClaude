#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SequencerData.h"
#include "SequencerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStepTriggered, int32, Row, int32, Step);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MUSICCLAUDE_API USequencerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USequencerComponent();

    UPROPERTY(BlueprintAssignable)
    FOnStepTriggered OnStepTriggered;

    UPROPERTY(BlueprintReadOnly)
    int32 CurrentStep = 0;

    void StartSequencer(USequencerData* InData);

    UFUNCTION(BlueprintCallable)
    void ResetPlayback();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    USequencerData* SequencerData = nullptr;

    FTimerHandle StepTimerHandle;

    void AdvanceStep();
};
