#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "BaseButtonWidget.generated.h"

// Extension point for shared button behavior (click feedback, cooldown, etc.).
// Add common logic here once two or more subclasses need the same thing.
UCLASS()
class MUSICCLAUDE_API UBaseButtonWidget : public UBaseWidget
{
    GENERATED_BODY()
};
