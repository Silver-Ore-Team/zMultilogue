
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
        oCNpc* m_Target = nullptr;
        oCNpc* m_Source = nullptr;
        Mode m_Mode = Mode::DEFAULT;
    public:
        oCNpc* GetTarget() const { return m_Target; }
        oCNpc* GetSource() const { return m_Source; }
        Mode GetMode() const { return m_Mode; }
        void Reset() {m_Target = nullptr; m_Source = nullptr; m_Mode = Mode::DEFAULT;}
        void SetNpcs(oCNpc* source, oCNpc* target);
        void SetMode(Mode mode);
        void EV_SetNpcs(oCNpc* source, oCNpc* target);
        void EV_SetMode(Mode mode);
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
        

    inline void zCMultilogueCameraAdapter::SetNpcs(oCNpc* source, oCNpc* target)
    {
        oCMsgManipulate* msg = new oCMsgManipulate( oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_CAMNPCS";
        msg->targetVob = target;
        msg->flag = (int)source;
        player->GetEM()->OnMessage(msg, player);
    }

    inline void zCMultilogueCameraAdapter::EV_SetNpcs(oCNpc* source, oCNpc* target)
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogueCameraAdapter::EV_SetNpcs");
        if (target) {
            m_Target = target;
            log->Debug("Target set to npc with id: {0}", target->idx);
        }
        if (source) {
            m_Source = source;
            log->Debug("Source set to npc with id: {0}", source->idx);
        }
        if (m_Target && m_Source && m_Mode == Mode::FULL) {
            player->ActivateDialogCam_Hook(0.0f);
        }
    }
}
