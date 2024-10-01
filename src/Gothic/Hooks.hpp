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


    // G2A: 0x00758130 public: int __thiscall oCNpc::ActivateDialogCam(float)
    // auto Ivk_oCNpc_ActivateDialogCam = Union::CreateHook(reinterpret_cast<void*>(0x00758130), &oCNpc::ActivateDialogCam_Hook);
    // int oCNpc::ActivateDialogCam_Hook(float p1)
    // {
    //     if (zMultilogue) {
    //         if (zMultilogue->IsRunning()) {
    //             oCNpc* target = zMultilogue->GetCameraAdapter()->GetTarget();
    //             if (target) {
    //                 this->talkOther = target;
    //             }
    //         }
    //     }
    //     return (this->*Ivk_oCNpc_ActivateDialogCam)(p1);
    // }

    auto Ivk_oCNpc_EV_Exchange = Union::CreateHook(reinterpret_cast<void*>(0x00753E30), &oCNpc::EV_Exchange_Hook);
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
        }
        return (this->*Ivk_oCNpc_EV_Exchange)(msg);
    }


}