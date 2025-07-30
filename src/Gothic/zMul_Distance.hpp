namespace GOTHIC_NAMESPACE {
    static float newDiagDist;

    class zCDialogDistanceController
    {
    private:
        float m_BackupDistance = 0;
        int m_Address = zSwitch(0x6B2A07, 0x758740) + 2;
    public:
        void SetDistance(float distance);
        float GetDefaultDistance();
        float GetDistance();
        void RestoreDistance() { SetDistance(m_BackupDistance); }
    };

    inline float zCDialogDistanceController::GetDefaultDistance()
    {
        if (!m_BackupDistance) {
            auto rawMem = ::Union::RawMemory::GetAccess(reinterpret_cast<void*>(m_Address), reinterpret_cast<void*>(m_Address + 0x4));
            void* addr = rawMem->Get<void*>(0);
            m_BackupDistance = sqrt(*static_cast<float*>(addr));
        }
        return m_BackupDistance;
    }

    inline void zCDialogDistanceController::SetDistance(float distance)
    {
        static NH::Logger* log = NH::CreateLogger("zMul::zCDialogDistanceController::SetDistance");
        GetDefaultDistance();
        newDiagDist = distance * distance;
        auto rawMem = ::Union::RawMemory::GetAccess(reinterpret_cast<void*>(m_Address), reinterpret_cast<void*>(m_Address + 0x4));
        rawMem->Get<int>(0) = reinterpret_cast<int>(&newDiagDist);
        rawMem->Push();
        log->Info("Distance set to {0}.", distance);
    }
}