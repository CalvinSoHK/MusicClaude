#include "MusicClaudeGameMode.h"

AMusicClaudeGameMode::AMusicClaudeGameMode()
{
    SequencerComponent = CreateDefaultSubobject<USequencerComponent>(TEXT("SequencerComponent"));
}

void AMusicClaudeGameMode::BeginPlay()
{
    SequencerData = NewObject<USequencerData>(this); // Must precede Super: Blueprint's Event BeginPlay fires inside Super::BeginPlay
    Super::BeginPlay();
    SequencerComponent->StartSequencer(SequencerData);
}
