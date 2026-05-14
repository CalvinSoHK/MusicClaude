@C:\Users\OUTIS\.claude\rulesets\engineering-rules.md

# Project Goal

Build a simple music game in Unreal Engine 5.4.4 to showcase Claude + UE collaboration.

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
     ├─ USequencerWidget           — custom-painted step grid; instrument labels, mouse input, playhead, grid lines;
     |                               binds OnStepTriggered → HandleStepTriggered → OnStepFired (BlueprintImplementableEvent)
     |                               binds OnStepAdvanced → HandleStepAdvanced (repaint)
     |                               binds OnGridCleared → HandleGridCleared (repaint)
     └─ UBaseButtonWidget          — extension point for shared button behavior; empty until two or more
          |                           subclasses need common logic
          ├─ UResetButtonWidget    — exposes ResetSequencer(); calls ResetPlayback()
          ├─ UClearButtonWidget    — exposes ClearSequencer(); calls ClearGrid()
          └─ UQuitButtonWidget     — exposes QuitGame(); calls UKismetSystemLibrary::QuitGame()

UActorComponent
  └─ USequencerComponent          — owns the step timer; advances CurrentStep (private, read via GetCurrentStep());
                                     broadcasts OnStepAdvanced (every step) and
                                     OnStepTriggered (active notes only);
                                     StartSequencer() and ResetPlayback() both delegate to RestartTimer()
UObject
  └─ USequencerData               — flat TArray<bool> grid (NumRows × NumSteps, row-major);
                                     BPM; ToggleStep/GetStep/ClearGrid; GetStepIntervalSeconds();
                                     broadcasts OnGridCleared after ClearGrid(); BlueprintType
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
| `SequencerWidget.h/.cpp` | Custom Slate paint, instrument labels, grid lines, playhead, mouse input |
| `BaseWidget.h/.cpp` | Shared widget base with InitWidget |
| `BaseButtonWidget.h/.cpp` | Button widget base (empty, for future buttons) |
| `ResetButtonWidget.h/.cpp` | Reset playback button |
| `ClearButtonWidget.h/.cpp` | Clear all grid nodes button |
| `QuitButtonWidget.h/.cpp` | Quit application button |
| `MusicClaudeGameMode.h/.cpp` | Game mode, wires data + component together |

### Audio Trigger Chain

1. `USequencerComponent` timer fires `AdvanceStep()` every `GetStepIntervalSeconds()`
   (60 / BPM / 2 for 8th notes at 120 BPM)
2. `CurrentStep` advances, then `OnStepAdvanced(Step)` broadcasts unconditionally
   (bound to `HandleStepAdvanced` on `USequencerWidget`, which calls `Invalidate(Paint)`)
3. Active nodes at that step broadcast `OnStepTriggered(Row, Step)`
4. `USequencerWidget::HandleStepTriggered` receives the broadcast and calls `OnStepFired(Row, Step)`
   (`BlueprintImplementableEvent` — the intermediate handler keeps binding pattern consistent)
5. `WBP_Sequencer` Blueprint handles `OnStepFired` and plays the corresponding audio cue

### Clear Trigger Chain

1. Blueprint calls `UClearButtonWidget::ClearSequencer()`
2. `USequencerData::ClearGrid()` zeroes the grid, then broadcasts `OnGridCleared`
3. `USequencerWidget::HandleGridCleared` receives the broadcast and calls `Invalidate(Paint)`
   (ensures the grid repaints immediately even when the sequencer is paused)

### Widget Initialization Pattern

All widgets call `InitWidget(USequencerData*, USequencerComponent*)` inherited from
`UBaseWidget`. The signature is uniform across all widgets; pass `nullptr` for whichever
dependency a widget does not use (e.g. button widgets receive `nullptr` for one or both).

`USequencerWidget` overrides `InitWidget_Implementation` to bind three delegates:
- `SequencerData->OnGridCleared` → `HandleGridCleared`
- `SequencerComponent->OnStepTriggered` → `HandleStepTriggered`
- `SequencerComponent->OnStepAdvanced` → `HandleStepAdvanced`

All three are unbound symmetrically in `NativeDestruct`.

Call site is `BP_MusicClaudeGameMode`'s Blueprint Event Graph: after `Parent: BeginPlay`,
the game mode creates `WBP_SequencerScreen`, adds it to viewport, then calls
`SetupSequencer` (a Blueprint function on `WBP_SequencerScreen`) which forwards
`SequencerData` and `SequencerComponent` to `InitWidget` on each child widget.

Initialization order guarantee: `SequencerData` is created via `NewObject` before
`Super::BeginPlay()` in C++, ensuring it is valid when Blueprint's Event BeginPlay fires.
(Blueprint's Event BeginPlay executes inside `Super::BeginPlay`, so data must exist first.)

### Grid Layout

- 4 rows (Kick, Snare, Tom, HiHat) × 32 steps
- Grid state stored as flat `TArray<bool>` in `USequencerData`; index = `Row * NumSteps + Step`
- Row display data (label + color) coupled in a `FRowStyle` struct array on `USequencerWidget`
- Label column: 120px wide; instrument names painted via `FCoreStyle` at 24pt, left of the grid
- Cell size: 40×60px; 4 bars, 8 steps per bar (8th-note resolution)
- Grid lines: bar start (2.5px bold), half-beat (1.5px mid), downbeat (1.0px pale)
- `"Slate"` module required in `MusicClaude.Build.cs` for `FCoreStyle` (`Styling/CoreStyle.h`)

### Module Conventions

- Log category: `LogMusicClaude` — declared in `MusicClaude.h`, defined in `MusicClaude.cpp`; use instead of `LogTemp` in all source files
- Game mode fields (`SequencerData`, `SequencerComponent`) are `protected UPROPERTY(BlueprintReadOnly)` — readable from Blueprint, not writable from external C++

### Blueprint Assets

| Asset path | Purpose |
|---|---|
| `Content/MusicClaude/BP_MusicClaudeGameMode` | Blueprint subclass of `AMusicClaudeGameMode` |
| `Content/MusicClaude/Widgets/WBP_Sequencer` | Extends `USequencerWidget`; handles `OnStepFired` for audio playback |
| `Content/MusicClaude/Widgets/WBP_SequencerScreen` | Top-level HUD; hosts grid + button widgets; calls `InitWidget` on all |
| `Content/MusicClaude/Widgets/WBP_ResetButton` | Extends `UResetButtonWidget`; button wired to `ResetSequencer()` |
| `Content/MusicClaude/Widgets/WBP_ClearButton` | Extends `UClearButtonWidget`; button wired to `ClearSequencer()` |
| `Content/MusicClaude/Widgets/WBP_QuitButton` | Extends `UQuitButtonWidget`; button wired to `QuitGame()` |
| `Content/MusicClaude/Rock_Kick/Snare/Hat/Tom_Cue` | Sound cues for each instrument row |
