#include "MusicClaudeGameMode.h"

AMusicClaudeGameMode::AMusicClaudeGameMode()
{
    SequencerComponent = CreateDefaultSubobject<USequencerComponent>(TEXT("SequencerComponent"));
}

void AMusicClaudeGameMode::BeginPlay()
{
    SequencerData = NewObject<USequencerData>(this);
    SequencerComponent->StartSequencer(SequencerData);

    Super::BeginPlay();
}
