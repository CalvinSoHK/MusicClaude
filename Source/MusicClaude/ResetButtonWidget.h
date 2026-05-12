#pragma once

#include "CoreMinimal.h"
#include "BaseButtonWidget.h"
#include "ResetButtonWidget.generated.h"

UCLASS()
class MUSICCLAUDE_API UResetButtonWidget : public UBaseButtonWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void ResetSequencer();
};
