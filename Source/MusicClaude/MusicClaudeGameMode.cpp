#include "MusicClaudeGameMode.h"

AMusicClaudeGameMode::AMusicClaudeGameMode()
{
    SequencerComponent = CreateDefaultSubobject<USequencerComponent>(TEXT("SequencerComponent"));
    SequencerData = CreateDefaultSubobject<USequencerData>(TEXT("SequencerData"));
}

void AMusicClaudeGameMode::BeginPlay()
{
    Super::BeginPlay();

    SequencerComponent->StartSequencer(SequencerData);
}
