
namespace GOTHIC_NAMESPACE {
    class zCMultilogueCameraAdapter
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
        void SetTarget(zCVob* target);
        void SetSource(zCVob* source);
        void SetMode(Mode mode);
        void CameraEvent();
        void EV_SetTarget(zCVob* target);
        void EV_SetSource(zCVob* source);
        void EV_SetMode(Mode mode);
        void EV_CameraEvent();
    };
    inline void zCMultilogueCameraAdapter::SetMode(Mode mode)
    {
        oCMsgManipulate* msg = new oCMsgManipulate(oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_CAMMODE";
        msg->flag = (int)mode;
        player->GetEM()->OnMessage(msg, player);
    }

    inline void zCMultilogueCameraAdapter::EV_SetMode(Mode mode)
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogueCameraAdapter::EV_SetMode");
        m_Mode = mode;
        log->Debug("Mode set to {0}", (int)mode);
    }
        

    inline void zCMultilogueCameraAdapter::SetSource(zCVob* source)
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogueCameraAdapter::SetSource");
        if (!source) {
            log->Warning("Invalid source.");
            return;
        }
        oCMsgManipulate* msg = new oCMsgManipulate( oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_CAMSOURCE";
        msg->targetVob = source;
        player->GetEM()->OnMessage(msg, player);
    }

    inline void zCMultilogueCameraAdapter::SetTarget(zCVob* target)
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogueCameraAdapter::SetTarget");
        if (!target) {
            log->Warning("Invalid target.");
            return;
        }
        oCMsgManipulate* msg = new oCMsgManipulate( oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_CAMTARGET";
        msg->targetVob = target;
        player->GetEM()->OnMessage(msg, player);
    }

    inline void zCMultilogueCameraAdapter::CameraEvent()
    {
        oCMsgManipulate* msg = new oCMsgManipulate( oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_CAMEVENT";
        player->GetEM()->OnMessage(msg, player);
    }

    inline void zCMultilogueCameraAdapter::EV_SetSource(zCVob* source)
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogueCameraAdapter::EV_SetSource");
        m_Source = source;
        log->Debug("Source " + GetVobString(source));
    }

    inline void zCMultilogueCameraAdapter::EV_SetTarget(zCVob* target)
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogueCameraAdapter::EV_SetTarget");
        m_Target = target;
        log->Debug("Target " + GetVobString(target));
    }

    inline void zCMultilogueCameraAdapter::EV_CameraEvent()
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogueCameraAdapter::EV_CameraEvent");
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
}
