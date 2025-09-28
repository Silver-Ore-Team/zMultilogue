// =========================================================
//
//  Dialog functions 
//
// =========================================================

/// Invites NPC to the multilog.
///
/// @param npc NPC to invite
func void zMul_Invite(var C_NPC npc) {};

/// Starts the multilog.
func void zMul_Start() {};

/// Changes talking NPC (must be invited first).
/// TIP: When adding choices to the dialog, `self` is automatically set to the dialog owner, so you don't need to call this function before `Info_AddChoice()`.
///
/// @global self will be set to the given NPC
/// @param npc Next talking NPC
func void zMul_Next(var C_NPC npc) {};

/// Finishes the multilog
/// TIP: Since `v0.1.10`, when calling `AI_StopProcessInfos()` there is no need to call `zMul_Finish()`.
func void zMul_Finish() {};

/// Makes invited NPC's wait for `npc` and each other.
///
/// @param npc NPC to wait for
func void zMul_Wait(var C_NPC npc)  {};

/// [deprecated] Continues the multilog to the next dialog choice.
/// Must be called before `Info_AddChoice`.
func void zMul_Continue() {};

/// Enables/disables automatic multilog mode, camera and NPC turning.
///
/// @param TRUE to enable, FALSE to disable
func void zMul_Auto(var int enable) {};

/// Enables/disables automatic multilog mode.
///
/// @param TRUE to enable, FALSE to disable
func void zMul_AutoMode(var int enable) {};

/// Enables/disables automatic NPC turning. 
/// NOTE: When enabled in manual mode, self and hero will be turning to each other.
///
/// @param TRUE to enable, FALSE to disable
func void zMul_AutoTurn(var int enable) {};

/// Enables/disables automatic camera.
///
/// @param TRUE to enable, FALSE to disable
func void zMul_AutoCam(var int enable) {};

// =========================================================
//
//  Camera functions 
//
// =========================================================

/// Changes the camera mode
/// @param mode camera mode (`0` = default, `1` = advanced, `2` = full)
func void zMulCam_SetMode(var int mode) {};

/// Sets the target and source NPC's for the camera
/// @param source source NPC
/// @param target target NPC
func void zMulCam_SetNpcs(var C_NPC source, var C_NPC target) {};

/// Sets the target NPC for the camera
/// @param npc target NPC
func void zMulCam_SetTargetNpc(var C_NPC npc) {};

/// Sets the source NPC for the camera
/// @param npc source NPC
func void zMulCam_SetSourceNpc(var C_NPC npc) {};

/// Sets the Target Vob for the camera
/// @param vobName name of the target Vob
func void zMulCam_SetTargetVob(var string vobName) {};

/// Sets the Source Vob for the camera
/// @param vobName name of the source Vob
func void zMulCam_SetSourceVob(var string vobName) {};

/// Executes the camera event
func void zMulCam_Event() {};

/// Resets the camera to the default state
func void zMulCam_Reset() {};
