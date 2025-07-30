# Concepts
Some concepts are used throughout the dialogs scripting. This page describes them in detail. If you are not familiar with dialogs scripting, you should read about [`C_INFO`](https://auronen.cokoliv.eu/gmc/zengin/scripts/classes/c_info/#information) and [`AI_Output()`](https://auronen.cokoliv.eu/gmc/zengin/scripts/externals/ai/#ai_output) first.

## Dialog
Speaking about a dialog in Gothic we usually mean a `C_INFO` instance. The dialog is a sequence of `AI_Output()` calls that are executed in a defined order. Calling the `AI_Output()` we define the speaker NPC, and the target NPC, but in vanilla scripts we are limited to the dialog owner (`self`) and the player (`other`/`hero`).

## Multilog
Multilog is a dialog that is not limited to a single speaker and a single target (same as a Trialog). It allows to have multiple NPCs speaking in a single `C_INFO` instance. Multilogs are designed to be contained within one `C_INFO` instance (dailog) and cannot exceed it.