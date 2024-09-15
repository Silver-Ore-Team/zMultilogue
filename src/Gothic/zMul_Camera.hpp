
namespace GOTHIC_NAMESPACE {
    class zCMultilogueCameraAdapter
    {
    private:
        oCNpc* target;
    public:
        void SetTarget(oCNpc* npc);
        oCNpc* GetTarget() { return target; }
    };

    void zCMultilogueCameraAdapter::SetTarget(oCNpc* npc)
    {
        target = npc;
    }
}
