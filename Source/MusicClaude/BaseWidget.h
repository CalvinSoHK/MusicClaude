#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SequencerData.h"
#include "SequencerComponent.h"
#include "BaseWidget.generated.h"

UCLASS()
class MUSICCLAUDE_API UBaseWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void InitWidget(USequencerData* InData, USequencerComponent* InComponent);
    virtual void InitWidget_Implementation(USequencerData* InData, USequencerComponent* InComponent);

protected:
    UPROPERTY(BlueprintReadOnly)
    USequencerData* SequencerData = nullptr;

    UPROPERTY(BlueprintReadOnly)
    USequencerComponent* SequencerComponent = nullptr;
};
