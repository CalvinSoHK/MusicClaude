# Reset Button Widget — Setup Guide

## What was built in C++

Three new classes form a widget hierarchy:

```
UBaseWidget          — holds SequencerData + SequencerComponent refs, unified InitWidget
  └─ UBaseButtonWidget   — base for all future sequencer buttons (empty for now)
       └─ UResetButtonWidget  — exposes ResetSequencer(), calls SequencerComponent->ResetPlayback()
```

`USequencerComponent` gained a `ResetPlayback()` function that clears the running timer, resets the step counter to 0, and restarts the timer cleanly.

---

## Step 1 — Compile

Hot-reload the project or use **Tools → Compile** in the Unreal editor. The new classes (`UBaseWidget`, `UBaseButtonWidget`, `UResetButtonWidget`) must be visible before creating Blueprints from them.

---

## Step 2 — Create WBP_ResetButton

1. In the Content Browser, right-click → **User Interface → Widget Blueprint**.
2. When prompted to pick a parent class, search for **ResetButtonWidget** and select it.
3. Name it `WBP_ResetButton`.
4. Open it and add a **Button** widget to the canvas. Inside the button add a **Text** block (e.g. "Reset").
5. In the button's **OnClicked** event (Details panel → Events → OnClicked → green `+` arrow):
   - Call **Reset Sequencer** (inherited from `UResetButtonWidget`).
6. Compile and save.

---

## Step 3 — Add WBP_ResetButton to WBP_SequencerScreen

1. Open **WBP_SequencerScreen**.
2. In the Designer, drag a **WBP_ResetButton** widget onto the canvas and position it wherever you want (e.g. below or above the sequencer grid).
3. Give it a variable name in the Details panel — e.g. `ResetButton` — so it's accessible from the Event Graph.

---

## Step 4 — Initialize the button

The reset button only needs the `SequencerComponent` reference — pass `None` for `SequencerData`.

Find wherever `WBP_Sequencer` is currently initialized in `WBP_SequencerScreen`'s Event Graph (the existing `InitWidget` call). Right after that call, add:

```
ResetButton → InitWidget(SequencerData: None, SequencerComponent: <your component ref>)
```

The `SequencerComponent` ref is the same one already used for the sequencer grid widget.

---

## Step 5 — Test

Press Play. Clicking the Reset button should snap the playhead back to step 0 and restart the timer, keeping the BPM intact.

---

## Adding more buttons in future

Create a new Widget Blueprint with **BaseButtonWidget** (or `UResetButtonWidget` as a model) as the parent. Add a `BlueprintCallable` UFUNCTION to the C++ class for the new action, call `InitWidget` the same way, and it will automatically have access to both `SequencerData` and `SequencerComponent`.
