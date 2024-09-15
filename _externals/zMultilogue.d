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