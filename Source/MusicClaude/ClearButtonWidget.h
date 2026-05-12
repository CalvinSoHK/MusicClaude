#pragma once

#include "CoreMinimal.h"
#include "BaseButtonWidget.h"
#include "ClearButtonWidget.generated.h"

UCLASS()
class MUSICCLAUDE_API UClearButtonWidget : public UBaseButtonWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void ClearSequencer();
};
