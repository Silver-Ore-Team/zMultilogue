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

    int zMulCam_SetNpcs()
    {
        zCParser* par = zCParser::GetParser();
        oCNpc* target = reinterpret_cast<oCNpc*>(par->GetInstance());
        oCNpc* source = reinterpret_cast<oCNpc*>(par->GetInstance());
        zMultilogue.Wait(player);
        zMultilogue.GetCameraAdapter().SetNpcs(source, target);
        return 0;
    };

    int zMulCam_SetMode()
    {
        zCParser* par = zCParser::GetParser();
        int mode; 
        par->GetParameter(mode);
        zMultilogue.Wait(player);
        zMultilogue.GetCameraAdapter().SetMode(static_cast<zCMultilogueCameraAdapter::Mode>(mode));
        return 0;
    };

    void DefineExternals()
    {
        parser->DefineExternal("ZMul_Invite", zMul_Invite, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMul_Start", zMul_Start, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMul_Finish", zMul_Finish, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMul_Next", zMul_Next, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMul_Wait", zMul_Wait, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMulCam_SetNpcs", zMulCam_SetNpcs, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMulCam_SetMode", zMulCam_SetMode, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
    }
}
