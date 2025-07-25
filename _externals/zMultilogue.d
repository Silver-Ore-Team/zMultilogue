// =========================================================
//
//  Dialog functions 
//
// =========================================================

/// Invites Npc to the Multilogue
///
/// @param slf Npc to invite
func void zMul_Invite(var C_NPC slf) {};

/// Starts the Multilogue
func void zMul_Start() {};

/// Changes talking NPC
///
/// @param slf Next talking NPC
func void zMul_Next(var C_NPC slf) {};

/// Finishes the Multilogue
func void zMul_Finish() {};

/// Makes invited NPC's wait for `slf` and each other
///
/// @param slf NPC to wait for
func void zMul_Wait(var C_NPC slf) {};

/// Enables/disables auto-turning of the NPCs
/// `talker`->`hero` and `hero`->`talker`
/// @param autoTurn `1` = enabled, `0` = disabled
func void zMul_AutoTurn(var int autoTurn) {};

/// Continues the Multilogue to the next dialog choice
/// Call it instead of `zMul_Finish` if you want to continue the dialog
/// Must be called before `Info_AddChoice`
func void zMul_Continue() {};

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

/// Resets the camera to the default state instantly
func void zMulCam_Reset() {};
