namespace GOTHIC_NAMESPACE {
    
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
                zMulCamera.EV_SetTarget(msg->targetVob);
                return TRUE;
            }
            if (msgSlot.Upper() == "EV_CAMSOURCE") {
                zMulCamera.EV_SetSource(msg->targetVob);
                return TRUE;
            }
            if (msgSlot.Upper() == "EV_CAMMODE") {
                zMulCamera.EV_SetMode(static_cast<zCMultilogueCamera::Mode>(msg->flag));
                return TRUE;
            }
            if (msgSlot.Upper() == "EV_CAMEVENT") {
                zMulCamera.EV_CameraEvent();
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
        static NH::Logger* log = NH::CreateLogger("zMul::oCNpc::ActivateDialogCam");
        if (zMulCamera.GetMode() != zCMultilogueCamera::Mode::DEFAULT) {
            
            zCVob* source = zMulCamera.GetSource();
            zCVob* target = zMulCamera.GetTarget();
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
        if (zMulCamera.GetMode() == zCMultilogueCamera::Mode::FULL) {
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
        else if (zMulCamera.GetMode() == zCMultilogueCamera::Mode::FULL) {
            reg.eip = zSwitch(0x004A9F17, 0x004B2393);
        }
    }

    void __fastcall oCSpawnManager_CheckRemoveNpc_PartialHook(Union::Registers& reg);
    auto Partial_oCSpawnManager_CheckRemoveNpc = Union::CreatePartialHook(reinterpret_cast<void*>(zSwitch(0x006D0CDD, 0x007795D8)), &oCSpawnManager_CheckRemoveNpc_PartialHook);
    void __fastcall oCSpawnManager_CheckRemoveNpc_PartialHook(Union::Registers& reg)
    {
        // Don't remove npc if it's in multilogue or dialogue with player
        if (zMulCamera.GetMode() != zCMultilogueCamera::Mode::DEFAULT) {
            oCNpc* npc = reinterpret_cast<oCNpc*>(reg.esi);
            if (npc) {
                if (zMultilogue.IsNpcInMultilogue(npc) || npc == player->talkOther) {
                    reg.eip = zSwitch(0x006D0DD0, 0x00779679);
                }
            }
        }
    }

    // AI_StopprocessInfos
    // G1:  int __cdecl sub_64F110()
    // G2A: int __cdecl sub_6DBB10() 
    void __fastcall sub_6DBB10_PartialHook();
    auto Partial_sub_6DBB10 = Union::CreatePartialHook(reinterpret_cast<void*>(zSwitch(0x0064F110, 0x006DBB10)), &sub_6DBB10_PartialHook);
    void __fastcall sub_6DBB10_PartialHook()
    {
        if (zMultilogue.IsRunning())
        {
            zMultilogue.Finish();
        }
    }

    // Info_AddChoice
    // G1:  int __cdecl sub_64F320()
    // G2A: int __cdecl sub_6DBE20()
    void __fastcall sub_6DBE20_PartialHook();
    auto Partial_sub_6DBE20 = Union::CreatePartialHook(reinterpret_cast<void*>(zSwitch(0x0064F320, 0x006DBE20)), &sub_6DBE20_PartialHook);
    void __fastcall sub_6DBE20_PartialHook()
    {
        if (zMultilogue.IsRunning())
        {
            // When displaying choices, we want to make dialog owner `self`
            oCNpc* owner = GetDialogOwner();
            if (owner != zMultilogue.GetLastSelf()) 
            {
                zMultilogue.MakeSelf(owner);
            }
        }
    }

    // G1:  0x0072CD90 protected: void __fastcall oCInformationManager::CollectInfos(void)
    // G2A: 0x00661AA0 protected: void __fastcall oCInformationManager::CollectInfos(void)
    auto Ivk_oCInformationManager_CollectInfos = Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x0072CD90, 0x00661AA0)), &oCInformationManager::CollectInfos_Hook);
    void oCInformationManager::CollectInfos_Hook(void)
    {
        // Finish multilogue when information manager is collecting new infos
        if (zMultilogue.IsRunning())
        {
            zMultilogue.Finish();
        }
        (this->*Ivk_oCInformationManager_CollectInfos)();
    }
    
}