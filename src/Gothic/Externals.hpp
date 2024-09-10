namespace GOTHIC_NAMESPACE {

    int zMul_Invite() {
        zCParser* par = zCParser::GetParser();
        oCNpc* npc;
        npc = (oCNpc*)par->GetInstance();

        if (!zMultilogue) {
            zMultilogue = new zCMultilogue();
        }
        zMultilogue->AddNpc(npc);
        return 0;
    };

    int zMul_Start() {
        auto log = NH::CreateLogger("Externals::zMul_Start");
        if (!zMultilogue) {
            log->Error("Multilogue not initialized.");
            return 1;
        }
        zMultilogue->Start();
        return 0;
    };

    int zMul_Finish() {
        auto log = NH::CreateLogger("Externals::zMul_Finish");
        if (!zMultilogue) {
            log->Error("Multilogue not initialized.");
            return 1;
        }
        zMultilogue->Finish();
        return 0;
    };


    void DefineExternals()
    {
        parser->DefineExternal("ZMul_Invite", zMul_Invite, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMul_Start", zMul_Start, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMul_Finish", zMul_Finish, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
    }
}
