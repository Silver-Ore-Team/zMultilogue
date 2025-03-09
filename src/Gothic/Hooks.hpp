namespace GOTHIC_NAMESPACE {
    //  G1: 0x006495B0 private: void __thiscall oCGame::DefineExternals_Ulfi(class zCParser *)
    // G1A: 0x006715F0 private: void __thiscall oCGame::DefineExternals_Ulfi(class zCParser *)
    //  G2: 0x00677A00 private: void __thiscall oCGame::DefineExternals_Ulfi(class zCParser *)
    // G2A: 0x006D4780 private: void __thiscall oCGame::DefineExternals_Ulfi(class zCParser *)
    void* oCGame_DefineExternals_Ulfi = reinterpret_cast<void*>(zSwitch(0x006495B0, 0x006715F0, 0x00677A00, 0x006D4780));
    void __fastcall DefineExternals_Ulfi_PartialHook()
    {
        DefineExternals();
    }
    auto Partial_DefineExternals_Ulfi = Union::CreatePartialHook(oCGame_DefineExternals_Ulfi, &DefineExternals_Ulfi_PartialHook);

    //  G1: 0x00424AF0 public: void __thiscall CGameManager::Run(void)
    // G1A: 0x004275D0 public: void __thiscall CGameManager::Run(void)
    //  G2: 0x004254F0 public: void __thiscall CGameManager::Run(void)
    // G2A: 0x00425830 public: void __thiscall CGameManager::Run(void)
    void* CGameManager_Run = reinterpret_cast<void*>(zSwitch(0x00424AF0, 0x004275D0, 0x004254F0, 0x00425830));
    void __fastcall CGameManager_Run_PartialHook() {
        ApplyOptions();
    };
    auto Partial_CGameManager_Run = Union::CreatePartialHook(CGameManager_Run, CGameManager_Run_PartialHook);

    // G1: 0x006AE310 protected: int __thiscall oCNpc::EV_Exchange(class oCMsgManipulate *)
    // G2A: 0x00753E30 protected: int __thiscall oCNpc::EV_Exchange(class oCMsgManipulate *)
    auto Ivk_oCNpc_EV_Exchange = Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x006AE310, 0x00753E30)), &oCNpc::EV_Exchange_Hook);
    int oCNpc::EV_Exchange_Hook( oCMsgManipulate* msg ) {
        zSTRING msgSlot = msg->slot;
        if (msgSlot) {
            if (msgSlot.Upper() == "EV_FINISH") {
                zMultilogue.EV_Finish();
                return TRUE;
            }
            if (msgSlot.Upper() == "EV_NEXT") {
                zMultilogue.EV_Next(msg->flag);
                return TRUE;
            }
            if (msgSlot.Upper() == "EV_CAMTARGET") {
                zMultilogue.GetCameraAdapter().EV_SetTarget(msg->targetVob);
                return TRUE;
            }
            if (msgSlot.Upper() == "EV_CAMSOURCE") {
                zMultilogue.GetCameraAdapter().EV_SetSource(msg->targetVob);
                return TRUE;
            }
            if (msgSlot.Upper() == "EV_CAMMODE") {
                zMultilogue.GetCameraAdapter().EV_SetMode(static_cast<zCMultilogueCameraAdapter::Mode>(msg->flag));
                return TRUE;
            }
            if (msgSlot.Upper() == "EV_CAMEVENT") {
                zMultilogue.GetCameraAdapter().EV_CameraEvent();
                return TRUE;
            }
        }
        return (this->*Ivk_oCNpc_EV_Exchange)(msg);
    }

    // G1: 0x006B2430 public: int __thiscall oCNpc::ActivateDialogCam(float)
    // G2A: 0x00758130 public: int __thiscall oCNpc::ActivateDialogCam(float)
    auto Ivk_oCNpc_ActivateDialogCam = Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x006B2430, 0x00758130)), &oCNpc::ActivateDialogCam_Hook);
    int oCNpc::ActivateDialogCam_Hook(float time)
    {
        static NH::Logger* log = NH::CreateLogger("oCNpc::ActivateDialogCam");
        if (zMultilogue.GetCameraAdapter().GetMode() != zCMultilogueCameraAdapter::Mode::DEFAULT) {
            
            zCVob* source = zMultilogue.GetCameraAdapter().GetSource();
            zCVob* target = zMultilogue.GetCameraAdapter().GetTarget();
            if (target && source) {
                zCArray<zCVob*> targetList;
                targetList.Insert(target);
                targetList.Insert(source);
                if (time>0.0f) ogame->GetCameraAI()->SetDialogCamDuration(time);
                auto mode = zSTRING("CAMMODDIALOG");
                ogame->GetCameraAI()->SetMode(mode, targetList);
                log->Info("Dialog camera activated. Source " + GetVobString(source) + " Target " + GetVobString(target));
                return TRUE;
            }
            log->Warning("Source or target is not set.");
        }
        return (this->*Ivk_oCNpc_ActivateDialogCam)(time);
    }

    void __fastcall oCNpc_EV_PlaySound_PartialHook(Union::Registers& reg);
    auto Partial_oCNpc_EV_PlaySound = Union::CreatePartialHook(reinterpret_cast<void*>(zSwitch(0x006B3124, 0x00758D97)), &oCNpc_EV_PlaySound_PartialHook);
    void __fastcall oCNpc_EV_PlaySound_PartialHook(Union::Registers& reg)
    {
        // Disable ActivateDialogCam call if camera mode is set to FULL
        if (zMultilogue.GetCameraAdapter().GetMode() == zCMultilogueCameraAdapter::Mode::FULL) {
            reg.eip = zSwitch(0x006B3130, 0x00758DA3);
        }
    }

    void __fastcall zCAICamera_StartDialogCam_PartialHook(Union::Registers& reg);
    auto Partial_zCAICamera_StartDialogCam = Union::CreatePartialHook(reinterpret_cast<void*>(zSwitch(0x004A9F00, 0x004B2378)), &zCAICamera_StartDialogCam_PartialHook);
    void __fastcall zCAICamera_StartDialogCam_PartialHook(Union::Registers& reg)
    {
        // Don't move camera durring first camera take
        int* numDialogCamTakes = reinterpret_cast<int*>(zSwitch(reg.ebp + 0x0CC, reg.ebx + 0x0D0));
        if (*numDialogCamTakes == 1) {
           return;
        }
        // Move camera durring the second camera take if needed
        else if (zMultilogue.GetCameraAdapter().GetMode() == zCMultilogueCameraAdapter::Mode::FULL) {
            reg.eip = zSwitch(0x004A9F17, 0x004B2393);
        }
    }

    void __fastcall oCSpawnManager_CheckRemoveNpc_PartialHook(Union::Registers& reg);
    auto Partial_oCSpawnManager_CheckRemoveNpc = Union::CreatePartialHook(reinterpret_cast<void*>(zSwitch(0x006D0CDD, 0x007795D8)), &oCSpawnManager_CheckRemoveNpc_PartialHook);
    void __fastcall oCSpawnManager_CheckRemoveNpc_PartialHook(Union::Registers& reg)
    {
        // Don't remove npc if it's in multilogue or dialogue with player
        if (zMultilogue.GetCameraAdapter().GetMode() != zCMultilogueCameraAdapter::Mode::DEFAULT) {
            oCNpc* npc = reinterpret_cast<oCNpc*>(reg.esi);
            if (npc) {
                if (zMultilogue.IsNpcInMultilogue(npc) || npc == player->talkOther) {
                    reg.eip = zSwitch(0x006D0DD0, 0x00779679);
                }
            }
        }
    }

}