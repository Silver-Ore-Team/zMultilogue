namespace GOTHIC_NAMESPACE {
    //  G1: 0x006495B0 private: void __thiscall oCGame::DefineExternals_Ulfi(class zCParser *)
    // G1A: 0x006715F0 private: void __thiscall oCGame::DefineExternals_Ulfi(class zCParser *)
    //  G2: 0x00677A00 private: void __thiscall oCGame::DefineExternals_Ulfi(class zCParser *)
    // G2A: 0x006D4780 private: void __thiscall oCGame::DefineExternals_Ulfi(class zCParser *)
    void* oCGame_DefineExternals_Ulfi = (void*)zSwitch(0x006495B0, 0x006715F0, 0x00677A00, 0x006D4780);
    void __fastcall DefineExternals_Ulfi_PartialHook(Union::Registers& reg)
    {
        Game_DefineExternals();
    }
    auto Partial_DefineExternals_Ulfi = Union::CreatePartialHook(oCGame_DefineExternals_Ulfi, &DefineExternals_Ulfi_PartialHook);
}