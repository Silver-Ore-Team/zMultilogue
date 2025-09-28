
namespace GOTHIC_NAMESPACE {
    class zCMultilogueCamera
    {
    public:
        enum Mode
        {
            DEFAULT,
            ADVANCED,
            FULL
        };
    private:
        zCVob* m_Target = nullptr;
        zCVob* m_Source = nullptr;
        Mode m_Mode = Mode::DEFAULT;
    public:
        zCVob* GetTarget() const { return m_Target; }
        zCVob* GetSource() const { return m_Source; }
        Mode GetMode() const { return m_Mode; }
        void Reset() {m_Target = nullptr; m_Source = nullptr; m_Mode = Mode::DEFAULT;}
        void ResetAI();
        void SetTarget(zCVob* target);
        void SetSource(zCVob* source);
        void SetMode(Mode mode);
        void SetModeInstant(Mode mode);
        void CameraEvent();
        void EV_SetTarget(zCVob* target);
        void EV_SetSource(zCVob* source);
        void EV_SetMode(Mode mode);
        void EV_CameraEvent();
        void EV_Reset() { Reset(); }
    };

    static zCMultilogueCamera zMulCamera {};

    inline void zCMultilogueCamera::SetMode(Mode mode)
    {
        oCMsgManipulate* msg = new oCMsgManipulate(oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_CAMMODE";
        msg->flag = (int)mode;
        player->GetEM()->OnMessage(msg, player);
    }

    inline void zCMultilogueCamera::SetModeInstant(Mode mode)
    {
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogueCamera::SetModeInstant");
        m_Mode = mode;
        log->Debug("Mode set to {0}", (int)mode);
    }
        
    inline void zCMultilogueCamera::EV_SetMode(Mode mode)
    {
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogueCamera::EV_SetMode");
        m_Mode = mode;
        log->Debug("Mode set to {0}", (int)mode);
    }
        
    inline void zCMultilogueCamera::SetSource(zCVob* source)
    {
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogueCamera::SetSource");
        if (!source) {
            log->Warning("Invalid source.");
            return;
        }
        oCMsgManipulate* msg = new oCMsgManipulate( oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_CAMSOURCE";
        msg->targetVob = source;
        player->GetEM()->OnMessage(msg, player);
    }

    inline void zCMultilogueCamera::SetTarget(zCVob* target)
    {
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogueCamera::SetTarget");
        if (!target) {
            log->Warning("Invalid target.");
            return;
        }
        oCMsgManipulate* msg = new oCMsgManipulate( oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_CAMTARGET";
        msg->targetVob = target;
        player->GetEM()->OnMessage(msg, player);
    }

    inline void zCMultilogueCamera::CameraEvent()
    {
        oCMsgManipulate* msg = new oCMsgManipulate( oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_CAMEVENT";
        player->GetEM()->OnMessage(msg, player);
    }

    inline void zCMultilogueCamera::EV_SetSource(zCVob* source)
    {
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogueCamera::EV_SetSource");
        m_Source = source;
        log->Debug("Source " + GetVobString(source));
    }

    inline void zCMultilogueCamera::EV_SetTarget(zCVob* target)
    {
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogueCamera::EV_SetTarget");
        m_Target = target;
        log->Debug("Target " + GetVobString(target));
    }

    inline void zCMultilogueCamera::EV_CameraEvent()
    {
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogueCamera::EV_CameraEvent");
        if (m_Mode != Mode::FULL) {
            return;
        }
        if (!m_Target) {
            log->Warning("Target is not set.");
            return;
        }
        if (!m_Source) {
            log->Warning("Source is not set.");
            return;
        }
        player->ActivateDialogCam_Hook(0.0f);
    }

    inline void zCMultilogueCamera::ResetAI()
    {
        oCMsgManipulate* msg = new oCMsgManipulate( oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_CAMRESET";
        player->GetEM()->OnMessage(msg, player);
    }
        
}
