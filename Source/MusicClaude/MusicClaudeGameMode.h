#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SequencerData.h"
#include "SequencerComponent.h"
#include "MusicClaudeGameMode.generated.h"

UCLASS()
class MUSICCLAUDE_API AMusicClaudeGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMusicClaudeGameMode();

    UPROPERTY(BlueprintReadOnly)
    USequencerData* SequencerData = nullptr;

    UPROPERTY(BlueprintReadOnly)
    USequencerComponent* SequencerComponent = nullptr;

protected:
    virtual void BeginPlay() override;
};
