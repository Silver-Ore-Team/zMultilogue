namespace GOTHIC_NAMESPACE {

    int zMul_Invite() {
        zCParser* par = zCParser::GetParser();
        oCNpc* npc = reinterpret_cast<oCNpc*>(par->GetInstance());
        zMultilogue.AddNpc(npc);
        return 0;
    };

    int zMul_Start() {
        zMultilogue.Start();
        return 0;
    };

    int zMul_Finish() {
        zMultilogue.Finish();
        return 0;
    };

    int zMul_Next() {
        zCParser* par = zCParser::GetParser();
        oCNpc* npc = reinterpret_cast<oCNpc*>(par->GetInstance());
        zMultilogue.MakeSelf(npc);
        return 0;
    };

    int zMul_Wait() {
        zCParser* par = zCParser::GetParser();
        oCNpc* npc = reinterpret_cast<oCNpc*>(par->GetInstance());
        zMultilogue.Wait(npc);
        return 0;
    };


    void DefineExternals()
    {
        parser->DefineExternal("ZMul_Invite", zMul_Invite, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMul_Start", zMul_Start, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMul_Finish", zMul_Finish, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMul_Next", zMul_Next, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMul_Wait", zMul_Wait, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
    }
}
