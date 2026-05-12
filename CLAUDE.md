@C:\Users\OUTIS\.claude\rulesets\engineering-rules.md

# Project Goal

Build a simple music game in Unreal Engine to showcase Claude + UE collaboration.

## Concept

A DAW-style sequencer game (similar to FL Studio's piano roll/step sequencer):

- A horizontal track grid where time moves left to right
- Each row represents one instrument
- Nodes placed on the grid trigger that instrument's audio sample when the playhead line passes over them
- The playhead loops continuously, playing back whatever pattern the player has arranged

## Scope

- Simple, demonstrable, and shippable — this is a showcase, not a full product
- Player interaction: place and remove nodes on the grid
- Visual feedback: playhead moves, nodes highlight on trigger
- Audio: each instrument row has its own sound cue that fires on node hit

## Architecture

### C++ Class Hierarchy

```
UUserWidget
  └─ UBaseWidget                  — shared SequencerData + SequencerComponent refs;
     |                               unified InitWidget (BlueprintNativeEvent)
     ├─ USequencerWidget           — custom-painted step grid; mouse input, playhead, grid lines
     └─ UBaseButtonWidget          — base for all sequencer action buttons (empty for now)
          └─ UResetButtonWidget    — exposes ResetSequencer(); calls ResetPlayback()

UActorComponent
  └─ USequencerComponent          — owns the step timer; advances CurrentStep;
                                     broadcasts OnStepAdvanced (every step) and
                                     OnStepTriggered (active notes only); ResetPlayback()
UObject
  └─ USequencerData               — 4×32 bool grid; BPM; ToggleStep/GetStep;
                                     GetStepIntervalSeconds(); BlueprintType
AGameMode
  └─ AMusicClaudeGameMode         — creates SequencerComponent via CreateDefaultSubobject;
                                     creates SequencerData via NewObject in BeginPlay
                                     (before Super::BeginPlay); calls StartSequencer after
```

### Key Source Files

| File | Purpose |
|---|---|
| `SequencerData.h/.cpp` | Grid state, BPM, step interval calculation |
| `SequencerComponent.h/.cpp` | Timer loop, step advancement, audio delegate, reset |
| `SequencerWidget.h/.cpp` | Custom Slate paint, grid lines, playhead, mouse input |
| `BaseWidget.h/.cpp` | Shared widget base with InitWidget |
| `BaseButtonWidget.h/.cpp` | Button widget base (empty, for future buttons) |
| `ResetButtonWidget.h/.cpp` | Reset playback button |
| `MusicClaudeGameMode.h/.cpp` | Game mode, wires data + component together |

### Audio Trigger Chain

1. `USequencerComponent` timer fires `AdvanceStep()` every `GetStepIntervalSeconds()`
   (60 / BPM / 2 for 8th notes at 120 BPM)
2. `CurrentStep` advances, then `OnStepAdvanced(Step)` broadcasts unconditionally
   (used by `USequencerWidget` to repaint the playhead on every step)
3. Active nodes at that step broadcast `OnStepTriggered(Row, Step)`
4. `USequencerWidget` receives `OnStepTriggered`, calls `OnStepFired(Row, Step)`
   (BlueprintImplementableEvent)
5. `WBP_Sequencer` Blueprint handles `OnStepFired` and plays the corresponding audio cue

### Widget Initialization Pattern

All widgets call `InitWidget(USequencerData*, USequencerComponent*)` inherited from
`UBaseWidget`. Pass `nullptr` for `SequencerData` on widgets that don't need grid data
(e.g. buttons). `USequencerWidget` overrides `InitWidget_Implementation` to also bind
both `OnStepTriggered` and `OnStepAdvanced` delegates.

Call site is `BP_MusicClaudeGameMode`'s Blueprint Event Graph: after `Parent: BeginPlay`,
the game mode creates `WBP_SequencerScreen`, adds it to viewport, then calls
`SetupSequencer` (a Blueprint function on `WBP_SequencerScreen`) which forwards
`SequencerData` and `SequencerComponent` to `InitWidget` on each child widget.

Initialization order guarantee: `SequencerData` is created via `NewObject` before
`Super::BeginPlay()` in C++, ensuring it is valid when Blueprint's Event BeginPlay fires.

### Grid Layout

- 4 rows (Kick, Snare, HiHat, Tom) × 32 steps
- Cell size: 40×60px; 4 bars, 8 steps per bar (8th-note resolution)
- Grid lines: bar start (2.5px bold), half-beat (1.5px mid), downbeat (1.0px pale)

### Blueprint Assets (Content/MusicClaude/)

| Asset | Purpose |
|---|---|
| `BP_MusicClaudeGameMode` | Blueprint subclass of `AMusicClaudeGameMode` |
| `WBP_Sequencer` | Extends `USequencerWidget`; handles `OnStepFired` for audio playback |
| `WBP_SequencerScreen` | Top-level HUD; hosts grid + button widgets; calls `InitWidget` on all |
| `WBP_ResetButton` | Extends `UResetButtonWidget`; button wired to `ResetSequencer()` |
| `Rock_Kick/Snare/Hat/Tom_Cue` | Sound cues for each instrument row |
