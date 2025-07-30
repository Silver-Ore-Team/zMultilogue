# Scripting Interface (Auto)
zMultilogue v0.2.0 introduced an auto interface for multilog scripting. This interface allows you to easily create multilogs without the need to manually set everything up.

## How it works
The auto interface works by forwarding the `AI_Output()` calls to a custom implementation that handles the multilogs automatically. This means that you can use the same `AI_Output()` calls as you would in a regular dialog, but the multilogs will be created and managed automatically. In addition, automatic camera and NPC turning could be enabled, so you don't have to worry about them.

## How to use
To use the auto interface, you need to enable auto mode in your dialog function. You can enable it wiht [`zMul_Auto()`](#zmul_auto) or [`zMul_AutoMode()`](#zmul_automode).

```dae
func void DIA_EXAMPLE_1()
{
	var C_NPC npc1; npc1 = Hlp_GetNpc(NONE_001_NPC);
	var C_NPC npc2; npc2 = Hlp_GetNpc(NONE_002_NPC);
	zMul_Auto(true);
	AI_Output(npc1, hero, "DIA_EXAMPLE_1_00");//Hey you!
	AI_Output(hero, npc1, "DIA_EXAMPLE_1_01");//Who, me?
	AI_Output(npc2, hero, "DIA_EXAMPLE_1_02");//Do you see anyone else here?
};
```

This will create a multilog with three NPCs (`hero`, `npc1`, and `npc2`) and three outputs. Multilog will be finished automatically when the last output is called. You can also use [`zMul_Finish()`](./manual-interface.md#zmul_finish) to finish the multilog manually.

## Functions

### `zMul_Auto`
Enables/disables automatic multilog mode, camera and NPC turning.
```dae
func void zMul_Auto(var int enable) {};
```
**Parameters**

  - `#!dae var int enalbe` - TRUE to enable, FALSE to disable

---
### `zMul_AutoMode`
Enables/disables automatic multilog mode.
```dae
func void zMul_AutoMode(var int enable) {};
```
**Parameters**

  - `#!dae var int enalbe` - TRUE to enable, FALSE to disable

---
### `zMul_AutoTurn`
Enables/disables automatic NPC turning.
```dae
func void zMul_AutoTurn(var int enable) {};
```
**Parameters**

  - `#!dae var int enalbe` - TRUE to enable, FALSE to disable

---
### `zMul_AutoCam`
Enables/disables automatic camera.
```dae
func void zMul_AutoCam(var int enable) {};
```
**Parameters**

  - `#!dae var int enalbe` - TRUE to enable, FALSE to disable

---
