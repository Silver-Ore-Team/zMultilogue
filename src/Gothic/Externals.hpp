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

    int zMulCam_SetNpcs()
    {
        zCParser* par = zCParser::GetParser();
        zCVob* target = reinterpret_cast<zCVob*>(par->GetInstance());
        zCVob* source = reinterpret_cast<zCVob*>(par->GetInstance());
        zMultilogue.GetCameraAdapter().SetSource(source);
        zMultilogue.GetCameraAdapter().SetTarget(target);
        WaitForPlayerAI();
        return 0;
    };

    int zMulCam_SetTargetNpc()
    {
        zCParser* par = zCParser::GetParser();
        oCNpc* npc = reinterpret_cast<oCNpc*>(par->GetInstance());
        zMultilogue.GetCameraAdapter().SetTarget(npc);
        WaitForPlayerAI();
        return 0;
    }

    int zMulCam_SetSourceNpc()
    {
        zCParser* par = zCParser::GetParser();
        oCNpc* npc = reinterpret_cast<oCNpc*>(par->GetInstance());
        zMultilogue.GetCameraAdapter().SetSource(npc);
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
            static NH::Logger* log = NH::CreateLogger("zMulCam_SetTargetVob");
            log->Warning("Vob not found: {0}", vobName.ToChar());
            return 0;
        }
        zMultilogue.GetCameraAdapter().SetTarget(vob);
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
            static NH::Logger* log = NH::CreateLogger("zMulCam_SetSourceVob");
            log->Warning("Vob not found: {0}", vobName.ToChar());
            return 0;
        }
        zMultilogue.GetCameraAdapter().SetSource(vob);
        WaitForPlayerAI();
        return 0;
    }

    int zMulCam_SetMode()
    {
        zCParser* par = zCParser::GetParser();
        int mode; 
        par->GetParameter(mode);
        zMultilogue.GetCameraAdapter().SetMode(static_cast<zCMultilogueCameraAdapter::Mode>(mode));
        WaitForPlayerAI();
        return 0;
    };

    int zMulCam_Event()
    {
        zMultilogue.GetCameraAdapter().CameraEvent();
        WaitForPlayerAI();
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
        parser->DefineExternal("ZMulCam_SetTargetNpc", zMulCam_SetTargetNpc, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMulCam_SetSourceNpc", zMulCam_SetSourceNpc, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMulCam_SetTargetVob", zMulCam_SetTargetVob, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMulCam_SetSourceVob", zMulCam_SetSourceVob, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMulCam_SetMode", zMulCam_SetMode, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);
        parser->DefineExternal("ZMulCam_Event", zMulCam_Event, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
    }
}
