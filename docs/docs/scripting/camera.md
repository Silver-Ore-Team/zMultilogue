# Camera System
zMultilogue provides a powerful camera system that allows you to take control over the dialog camera during conversations. This is particularly useful when creating multilogs where default camera could not be enough. The camera system is independent of the main multilog system, meaning you can use it in any dialog.

## Working principle

Dialog camera operates based on `Source` and `Target` vobs[^1]. `Source` is the object from behind which the camera is casted and `Target` is the object at which the camera is casted. At every `AI_Output()` call it is checked if the speaker has changed and if so the camera event is executed. zMultilogue allows to change `Source` and `Target` and also ecxeute camera events independent.

## Camera modes

  1. Default - Default dialog camera
  2. Advanced - `Source` and `Target` are controlled by the user, camera events are automatic
  3. Full - `Source`, `Target` and camera events are controlled by the user

## Functions

### `zMulCam_SetMode`
Changes the camera mode
```dae
func void zMulCam_SetMode(var int mode) {};
```
**Parameters**

  - `#!dae var int mode` - camera mode (`0` = default, `1` = advanced, `2` = full)

---
### `zMulCam_SetNpcs`
Sets the target and source NPC's for the camera
```dae
func void zMulCam_SetNpcs(var C_NPC source, var C_NPC target) {};
```
**Parameters**

  - `#!dae var C_NPC source` - source NPC
  - `#!dae var C_NPC target` - target NPC

---
### `zMulCam_SetTargetNpc`
Sets the target NPC for the camera
```dae
func void zMulCam_SetTargetNpc(var C_NPC npc) {};
```
**Parameters**

  - `#!dae var C_NPC target` - target NPC

---
### `zMulCam_SetSourceNpc`
Sets the source NPC for the camera
```dae
func void zMulCam_SetSourceNpc(var C_NPC npc) {};
```
**Parameters**

  - `#!dae var C_NPC npc` - source NPC

---
### `zMulCam_SetTargetVob`
Sets the target Vob for the camera
```dae
func void zMulCam_SetTargetVob(var string vobName) {};
```
**Parameters**

  - `#!dae var string vobName` - name of the target Vob

---
### `zMulCam_SetSourceVob`
Sets the source Vob for the camera
```dae
func void zMulCam_SetSourceVob(var string vobName) {};
```
**Parameters**

  - `#!dae var string vobName` - name of the source Vob

---
### `zMulCam_Event`
Executes the camera event
!!! Warning
    This function is only available in `FULL` camera mode. In `ADVANCED` events are executed during `AI_Output()` calls.
```dae
func void zMulCam_Event() {};
```

---
### `zMulCam_Reset`
Resets the camera to the default state
```dae
func void zMulCam_Reset() {};
```

## Example
You can use the camera system e.g. to lock the camera on the NPC for the whole dialog. Below is an example of how to do that:

```dae
func void DIA_EXAMPLE_3()
{
  // Set camera mode to FULL
  zMulCam_SetMode(2); 
  // Set source and target NPCs
  zMulCam_SetSourceNpc(hero);
  zMulCam_SetTargetNpc(self);
  // Execute camera event
  zMulCam_Event();
  // Now the camera is locked on self for the whole dialog
  AI_Output(self, hero, "DIA_EXAMPLE_3_00");//Hey you!
  AI_Output(hero, self, "DIA_EXAMPLE_3_01");//Who, me?
};
```

[^1]: 
    Vobs are virtual objects in the game world. Read more on [Gothic Modding Community](https://auronen.cokoliv.eu/gmc/zengin/worlds/Classes/zCVob/).