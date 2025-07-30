namespace GOTHIC_NAMESPACE {

    // Helper function to wait for the player AI events
    void WaitForPlayerAI()
    {
        if (zMultilogue.IsRunning()) {
            zMultilogue.Wait(player);
        }
        else if (player->state.IsInState(parser->GetIndex("ZS_TALK"))) {
            AI_WaitTillEnd(player->talkOther, player);
        }
    }

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

    int zMul_AutoTurn()
    {
        zCParser* par = zCParser::GetParser();
        int autoTurn;
        par->GetParameter(autoTurn);
        zMultilogue.SetAutoTurn(autoTurn != 0);
        return 0;
    };

    int zMulCam_SetNpcs()
    {
        zCParser* par = zCParser::GetParser();
        zCVob* target = reinterpret_cast<zCVob*>(par->GetInstance());
        zCVob* source = reinterpret_cast<zCVob*>(par->GetInstance());
        zMulCamera.SetSource(source);
        zMulCamera.SetTarget(target);
        WaitForPlayerAI();
        return 0;
    };

    int zMulCam_SetTargetNpc()
    {
        zCParser* par = zCParser::GetParser();
        oCNpc* npc = reinterpret_cast<oCNpc*>(par->GetInstance());
        zMulCamera.SetTarget(npc);
        WaitForPlayerAI();
        return 0;
    }

    int zMulCam_SetSourceNpc()
    {
        zCParser* par = zCParser::GetParser();
        oCNpc* npc = reinterpret_cast<oCNpc*>(par->GetInstance());
        zMulCamera.SetSource(npc);
        WaitForPlayerAI();
        return 0;
    }

    int zMulCam_SetTargetVob()
    {
        zCParser* par = zCParser::GetParser();
        zSTRING vobName;
        par->GetParameter( vobName );
        oCWorld* world = ogame->GetGameWorld();
        zCVob* vob = world->SearchVobByName( vobName );
        if (!vob)
        {
            static NH::Logger* log = NH::CreateLogger("zMul::Externals::zMulCam_SetTargetVob");
            log->Warning("Vob not found: {0}", vobName.ToChar());
            return 0;
        }
        zMulCamera.SetTarget(vob);
        WaitForPlayerAI();
        return 0;
    }

    int zMulCam_SetSourceVob()
    {
        zCParser* par = zCParser::GetParser();
        zSTRING vobName;
        par->GetParameter( vobName );
        oCWorld* world = ogame->GetGameWorld();
        zCVob* vob = world->SearchVobByName( vobName );
        if (!vob) {
            static NH::Logger* log = NH::CreateLogger("zMul::Externals::zMulCam_SetSourceVob");
            log->Warning("Vob not found: {0}", vobName.ToChar());
            return 0;
        }
        zMulCamera.SetSource(vob);
        WaitForPlayerAI();
        return 0;
    }

    int zMulCam_SetMode()
    {
        zCParser* par = zCParser::GetParser();
        int mode; 
        par->GetParameter(mode);
        zMulCamera.SetMode(static_cast<zCMultilogueCamera::Mode>(mode));
        WaitForPlayerAI();
        return 0;
    };

    int zMulCam_Event()
    {
        zMulCamera.CameraEvent();
        WaitForPlayerAI();
        return 0;
    };

    int zMul_Continue()
    {
        static NH::Logger* log = NH::CreateLogger("zMul::Externals::zMul_Continue");
        log->Warning("This function is deprecated");
        // Leave for compatibility
        WaitForPlayerAI();
        return 0;
    }

    int zMulCam_Reset()
    {
        zMulCamera.Reset();
        return 0;
    }

    int zMul_Auto()
    {
        zCParser* par = zCParser::GetParser();
        int autoMode;
        par->GetParameter(autoMode);
        zMultilogue.SetAutoMode(autoMode != 0);
        zMultilogue.SetAutoTurn(autoMode != 0);
        zMultilogue.SetAutoCam(autoMode != 0);
        return 0;
    }

    int zMul_AutoMode()
    {
        zCParser* par = zCParser::GetParser();
        int autoMode;
        par->GetParameter(autoMode);
        zMultilogue.SetAutoMode(autoMode != 0);
        return 0;
    }

    int zMul_AutoCam()
    {
        zCParser* par = zCParser::GetParser();
        int autoCam;
        par->GetParameter(autoCam);
        zMultilogue.SetAutoCam(autoCam != 0);
        return 0;
    }

    void DefineExternals()
    {
        parser->DefineExternal("zMul_Invite", zMul_Invite, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("zMul_Start", zMul_Start, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
        parser->DefineExternal("zMul_Finish", zMul_Finish, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
        parser->DefineExternal("zMul_Next", zMul_Next, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("zMul_Wait", zMul_Wait, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("zMul_Continue", zMul_Continue, zPAR_TYPE_VOID, zPAR_TYPE_VOID);

        parser->DefineExternal("zMul_Auto", zMul_Auto, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
        parser->DefineExternal("zMul_AutoMode", zMul_AutoMode, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
        parser->DefineExternal("zMul_AutoTurn", zMul_AutoTurn, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
        parser->DefineExternal("zMul_AutoCam", zMul_AutoCam, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
        
        parser->DefineExternal("zMulCam_SetNpcs", zMulCam_SetNpcs, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("zMulCam_SetTargetNpc", zMulCam_SetTargetNpc, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("zMulCam_SetSourceNpc", zMulCam_SetSourceNpc, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("zMulCam_SetTargetVob", zMulCam_SetTargetVob, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
        parser->DefineExternal("zMulCam_SetSourceVob", zMulCam_SetSourceVob, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
        parser->DefineExternal("zMulCam_SetMode", zMulCam_SetMode, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
        parser->DefineExternal("zMulCam_Event", zMulCam_Event, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
        parser->DefineExternal("zMulCam_Reset", zMulCam_Reset, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
    }
}
