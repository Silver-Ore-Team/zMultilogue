
namespace GOTHIC_NAMESPACE {
    class zCMultilogueCameraAdapter
    {
    private:
        oCNpc* m_Target = nullptr;
    public:
        void SetTarget(oCNpc* npc);
        oCNpc* GetTarget() const { return m_Target; }
    };

    inline void zCMultilogueCameraAdapter::SetTarget(oCNpc* npc)
    {
        m_Target = npc;
    }
}
