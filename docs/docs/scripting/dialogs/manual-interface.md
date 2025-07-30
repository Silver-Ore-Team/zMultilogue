# Scripting Interface (Manual)
From the very beginning, zMultilogue has provided an interface for scripting multilogs based on the [LeGo Trialoge package](https://auronen.cokoliv.eu/gmc/zengin/scripts/extenders/lego/applications/trialoge/). This interface requires manual setup of multilogs, which can be cumbersome for larger scripts. However, it offers a lot of flexibility and control over the multilogs.

## How it works
The manual interface works fliping the `self` variable beetween the invited NPCs. That means that you can use the same `AI_Output()` calls as you would in a regular dialog, but you will be responsible for managing who the `self` is at the moment.

## How to use
To use the manual interface, you need to setup everything manually. You can do this by inviting NPCs to the multilog using [`zMul_Invite()`](#zmul_invite) and then starting the multilog with [`zMul_Start()`](#zmul_start). Then you can use [`zMul_Next()`](#zmul_next) to switch the `self` variable to the next NPC in the multilog.

```dae
func void DIA_EXAMPLE_2()
{
    var C_NPC npc1; npc1 = Hlp_GetNpc(NONE_001_NPC);
    var C_NPC npc2; npc2 = Hlp_GetNpc(NONE_002_NPC);
    // let's supose that npc1 is the owner of the dialog so there is no need to invite him
    zMul_Invite(npc2);
    zMul_Start();
    // npc1 is now the self
    AI_Output(self, hero, "DIA_EXAMPLE_2_00");//Hey you!
    AI_Output(hero, self, "DIA_EXAMPLE_2_01");//Who, me?
    zMul_Next(npc2);
    // npc2 is now the self
    AI_Output(self, hero, "DIA_EXAMPLE_2_02");//Do you see anyone else here?
    zMul_Finish();
};
```

## Functions

### `zMul_Invite`
Invites NPC to the multilog.
```dae
func void zMul_Invite(var C_NPC slf)  {};
```
**Parameters**

  - `#!dae var C_NPC slf` - NPC to be invited

---
### `zMul_Start`
Starts the multilog.
```dae
func void zMul_Start() {};
```

---
### `zMul_Next`
Changes talking NPC (must be invited first). The `self` variable will be set to the given NPC.
!!! Tip
    When adding choices to the dialog, `self` is automatically set to the dialog owner, so you don't need to call this function before `Info_AddChoice()`.
```dae
func void zMul_Next(var C_NPC npc)  {};
```
**Parameters**

  - `#!dae var C_NPC npc` - Next talking NPC

---
### `zMul_Finish`
Finishes the multilog.
!!! Tip
    Since [`v0.1.10`](https://github.com/Silver-Ore-Team/zMultilogue/releases/tag/v0.1.10), when calling `AI_StopProcessInfos()` there is no need to call `zMul_Finish()`.
```dae
func void zMul_Finish() {};
```

---
### `zMul_Wait`
Makes invited NPC's wait for `npc` and each other.
```dae
func void zMul_Wait(var C_NPC npc)  {};
```
**Parameters**

  - `#!dae var C_NPC npc` - NPC to wait for

---
### `zMul_Continue`
Continues the multilog to the next dialog choice.  
Must be called before `Info_AddChoice()`.
!!! failure "Deprecated"
    This function is deprecated since [`v0.1.10`](https://github.com/Silver-Ore-Team/zMultilogue/releases/tag/v0.1.10).
```dae
func void zMul_Continue() {};
```

---
### `zMul_AutoTurn`
Enables/disables automatic NPC turning.
!!! Note
    When enabled in manual mode, `self` and hero will be turning to each other.
```dae
func void zMul_AutoTurn(var int enable) {};
```
**Parameters**

  - `#!dae var int enalbe` - TRUE to enable, FALSE to disable
