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
