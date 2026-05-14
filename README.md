# MusicClaude

A DAW-style step sequencer built in Unreal Engine 5, developed as a hands-on project for learning UE5 C++ and collaborating with Claude AI.

## What It Is

MusicClaude is a music game inspired by FL Studio's step sequencer. A playhead sweeps left to right across a grid, where each row represents an instrument (Kick, Snare, Tom, Hi-Hat). Any node you place on the grid fires that instrument's audio sample when the playhead crosses it. The loop runs continuously, so you hear your pattern play back in real time as you build it.

The interface is entirely custom-painted in C++ using Unreal's Slate layer, with no pre-built UI components. Clicking a cell toggles it on or off. Three buttons round out the controls: reset the playhead, clear the whole grid, and quit.

## Scope

This is a deliberately small, shippable project. The goal was to produce something complete and demonstrable, not a feature-rich DAW.

What's in:
- 4 instrument rows x 32 steps (8th-note resolution at 120 BPM)
- Real-time audio playback via Unreal Sound Cues
- Custom-painted grid with bar markers, playhead, and note highlighting
- Reset, clear, and quit controls

What's intentionally out:
- Saving/loading patterns
- Variable BPM or time signature
- Additional instruments or sample swapping

## Why This Project Exists

I built this to get comfortable with Unreal Engine 5 C++ coming from five years of Unity and C# development. UE5 is a large, opinionated framework, and I wanted a real project rather than following a tutorial. Something that compiles, runs, and does something tangible.

I used Claude AI as a collaborator throughout, for planning the architecture, writing and reviewing C++, and working through UE5-specific patterns like `UUserWidget` subclassing, delegate binding, and the Slate paint API. The process was as much about developing good habits with AI tooling as it was about shipping the game itself.

The main thing I learned is that Claude needs guardrails when working inside a complex engine like UE5. Engine APIs shift between versions and the editor adds layers of abstraction that aren't always obvious from documentation alone. The most common failure mode was lifecycle code. Claude would produce code that was correct in isolation but conflicted with how UE5's own `BeginPlay`, `Construct`, or timer systems expected to be called. Catching those interactions early, and being explicit about lifecycle order in my prompts, made the difference between sessions that compounded on each other and sessions that had to be unwound.

## Architecture Overview

The project is pure C++ with Blueprint used only for wiring, with a clean separation of concerns:

| Layer | Class | Role |
|---|---|---|
| Data | `USequencerData` | Grid state (`TArray<bool>`), BPM, step interval |
| Logic | `USequencerComponent` | Timer loop, step advancement, audio delegates |
| UI | `USequencerWidget` | Custom Slate paint, mouse input, playhead rendering |
| Buttons | `UResetButtonWidget`, `UClearButtonWidget`, `UQuitButtonWidget` | Thin wrappers calling into data/component |
| Game Mode | `AMusicClaudeGameMode` | Wires data + component together, owns both |

Audio is triggered via a delegate chain. The component's timer fires `OnStepTriggered`, the widget relays it to a `BlueprintImplementableEvent`, and the Blueprint asset plays the corresponding Sound Cue.

## Built With

- Unreal Engine 5.4.4
- C++ (Slate, UMG, gameplay framework)
- Claude AI (architecture, C++ implementation, code review)

*This project was developed in collaboration with [Claude](https://claude.ai) by Anthropic.*
