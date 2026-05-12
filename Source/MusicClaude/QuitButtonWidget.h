#pragma once

#include "CoreMinimal.h"
#include "BaseButtonWidget.h"
#include "QuitButtonWidget.generated.h"

UCLASS()
class MUSICCLAUDE_API UQuitButtonWidget : public UBaseButtonWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void QuitGame();
};
