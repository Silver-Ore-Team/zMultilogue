#include <unordered_map>

namespace GOTHIC_NAMESPACE
{
    class zCMultilogue
    {
    private:
        zCMultilogueCameraAdapter m_CameraAdapter;
        zCDialogDistanceController m_DistanceController;
        oCNpc* m_LastSelf = nullptr;
        std::unordered_map<int, oCNpc*> m_Npcs;
        bool m_Running = false;
        bool m_AutoTurn = false;
    public:
        void AddNpc(oCNpc* npc);
        void Start();
        void Finish();
        void ListNpcs();
        void MakeSelf(oCNpc* npc);
        void Wait (oCNpc* npc);
        bool IsRunning() const { return m_Running; }
        bool IsNpcInMultilogue(oCNpc* npc) const { return m_Npcs.contains(npc->idx); }
        zCMultilogueCameraAdapter& GetCameraAdapter() { return m_CameraAdapter; }
        void EV_Finish();
        void EV_Next(int id);
        void Reset();
        void SetAutoTurn(bool autoTurn) { m_AutoTurn = autoTurn; }
        void Continue();
    };

    static zCMultilogue zMultilogue = zCMultilogue{}; // Global instance


    inline void zCMultilogue::AddNpc(oCNpc* npc)
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::AddNpc");
        if (!npc) {
            log->Warning("Invalid NPC");
            return;
        }
        if (m_Npcs.contains(npc->idx)) {
            log->Warning("NPC with ID {0} already exists.", npc->idx);
            return;
        }
        if (Npc_IsInActiveVoblist(npc)) {
            npc->ClearEM();
        }
        oCNpc* self = GetSelfInstance();
        npc->state.StartAIState("ZS_MULTILOGUE", 0, 0, 0, 0);
        parser->SetInstance("SELF", self);
        m_Npcs[npc->idx] = npc;
        log->Info("NPC with ID {0} added.", npc->idx);
    }

    inline void zCMultilogue::Start()
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::Start");
        if (m_Running) {
            log->Warning("Multilogue already running.");
            return;
        }
        oCNpc* self = GetSelfInstance();
        if (!self) {
            log->Error("Failed to get SELF instance.");
            return;
        }
        m_AutoTurn = false;
        m_LastSelf = self;
        AddNpc(self);
        AddNpc(player);
        Npc_FakeTalkState(self);
        m_Running = true;
        Wait(self);
        log->Info("Starting multilogue with {0} NPCs.", m_Npcs.size());
        ListNpcs();
    }

    inline void zCMultilogue::Finish()
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::Finish");
        if (!m_Running) {
            log->Warning("Multilogue not Running.");
            return;
        }
        static oCInformationManager& mgrInfos = oCInformationManager::GetInformationManager();
        if (!ogame->infoman) {
            log->Error("infoman not found.");
            return;
        }
        if (!mgrInfos.Npc) {
            log->Error("mgrInfos.Npc is invalid.");
            return;
        }
        if (!mgrInfos.Player) {
            log->Error("mgrInfos.Player is invalid.");
            return;
        }

        MakeSelf(mgrInfos.Npc);

        oCNpc* slf = mgrInfos.Npc;
        oCNpc* oth = mgrInfos.Player;

        // nie wiem czy to potrzebne
        // ---
        AI_WaitTillEnd(slf, oth);
        AI_WaitTillEnd(oth, slf);

        Wait (slf);
        Wait (oth);
        // ---

        oCMsgManipulate* msg = new oCMsgManipulate( oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_FINISH";
        player->GetEM()->OnMessage(msg, player);
        // Add EV_PROCESSINFOS at the end of a dialogue to prevent stuck when not calling AI_Stopprocesinfos
        m_LastSelf->GetEM()->OnMessage( new oCMsgConversation( oCMsgConversation::EV_PROCESSINFOS), player );
    }


    inline void zCMultilogue::EV_Finish() {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::EV_Finish");
        if (!m_Running) {
            log->Warning("Multilogue has already finished.");
            return;
        }
        m_Running = false;
        m_LastSelf = nullptr;
        m_DistanceController.RestoreDistance();
        static oCInformationManager& mgrInfos = oCInformationManager::GetInformationManager();
        if (!mgrInfos.Npc) {
            log->Error("mgrInfos.Npc is invalid.");
            return;
        }
        player->talkOther = mgrInfos.Npc;
        for (auto& [key, npc] : m_Npcs) {
            if (npc && npc != player && npc != mgrInfos.Npc) {
                npc->talkOther = nullptr;
                npc->state.StartRtnState(1); // Force routine exchange
            }
        }
        log->Info("Finishing multilogue with {0} NPCs.", m_Npcs.size());
        m_Npcs.clear();
    }


    inline void zCMultilogue::ListNpcs() {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::ListNpcs");
        std::string npcList = "Current NPCs: ";
        for (auto& [key, value] : m_Npcs) {
            npcList += std::to_string(key) + ", ";
        }
        if (!m_Npcs.empty()) {
            npcList.pop_back(); // Remove the last space
            npcList.pop_back(); // Remove the last comma
        }
        log->Info(npcList.c_str());
    }

    inline void zCMultilogue::Wait(oCNpc* npc) {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::Wait");
        if (!npc) {
            log->Warning("Invalid NPC.");
            return;
        }
        if (!m_Npcs.contains(npc->idx)) {
            log->Warning("NPC with ID {0} is not in the multilogue", npc->idx);
            return;
        }
        AI_WaitTillEnd(m_LastSelf, npc);
        AI_WaitTillEnd(npc, m_LastSelf);

        //Sync hero with new npc & npc with hero
        AI_WaitTillEnd(player, npc);
        AI_WaitTillEnd(npc, player);

        //Sync all Npcs invited to trialogue
        oCNpc* lastNpc = std::prev(m_Npcs.end())->second;

        for (auto & [id, currentNpc]: m_Npcs) {
            if (lastNpc && currentNpc) {
                AI_WaitTillEnd(npc, currentNpc);
            }
            lastNpc = currentNpc;
        }
    }

    inline void zCMultilogue::MakeSelf(oCNpc *npc) {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::MakeSelf");
        if (!npc) {
            log->Warning("Invalid NPC.");
            return;
        }
        if (!m_Npcs.contains(npc->idx)) {
            log->Warning("NPC with ID {0} is not in the multilogue", npc->idx);
            return;
        }
        if (npc->idx == m_LastSelf->idx) {
            log->Warning("NPC {0} is already a self.", npc->idx);
            return;
        }
        if (npc->idx == player->idx) {
            log->Warning("NPC {0} is a player.", npc->idx);
            return;
        }
        m_LastSelf = npc;
        Wait(npc);
        oCMsgManipulate* msg = new oCMsgManipulate( oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_NEXT";
        msg->flag = npc->idx;
        player->GetEM()->OnMessage(msg, player);
        parser->SetInstance("SELF", m_LastSelf);
        Npc_FakeTalkState(npc);
        Wait(npc);
        // Self and player will turn to each other if m_AutoTurn is enabled
        if (m_AutoTurn) {
            m_LastSelf->GetEM()->OnMessage(new oCMsgMovement(oCMsgMovement::EV_TURNTOVOB, player), m_LastSelf);
            player->GetEM()->OnMessage(new oCMsgMovement(oCMsgMovement::EV_TURNTOVOB, m_LastSelf), player);
        }
    }

    inline void zCMultilogue::EV_Next(int id) {
        oCNpc* npc = m_Npcs.find(id)->second;
        if (npc) {
            static NH::Logger* log = NH::CreateLogger("zCMultilogue::EV_Next");
            log->Info("Next NPC: {0}", id);
            npc->talkOther = nullptr;

            float npcDistance = player->GetDistanceToVobApprox(*npc);
            log->Debug("Distance to player: {0}", npcDistance);
            npcDistance += 200.0f; // Add some buffer
            if (npcDistance > m_DistanceController.GetDefaultDistance()) {
                m_DistanceController.SetDistance(npcDistance);
            }
        }
    }

    inline void zCMultilogue::Reset() {
        m_CameraAdapter = zCMultilogueCameraAdapter{};
        m_DistanceController = zCDialogDistanceController{};
        m_LastSelf = nullptr;
        m_Npcs.clear();
        m_Running = false;
    }

    inline void zCMultilogue::Continue() {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::Continue");
        if (!m_Running) {
            log->Warning("Multilogue is not running.");
            return;
        }
        static oCInformationManager& mgrInfos = oCInformationManager::GetInformationManager();
        MakeSelf(mgrInfos.Npc);
        m_LastSelf->GetEM()->OnMessage( new oCMsgConversation( oCMsgConversation::EV_PROCESSINFOS), player );
    }

}