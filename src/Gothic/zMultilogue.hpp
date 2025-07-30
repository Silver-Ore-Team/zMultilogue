#include <unordered_map>

namespace GOTHIC_NAMESPACE
{
    class zCMultilogue
    {
    private:
        zCDialogDistanceController m_DistanceController;
        oCNpc* m_LastSelf = nullptr;
        std::unordered_map<int, oCNpc*> m_Npcs;
        bool m_Running = false;
        bool m_AutoTurn = false;
        bool m_AutoMode = false;
        bool m_AutoCam = false;
    public:
        void AddNpc(oCNpc* npc);
        void Start();
        void Finish();
        void ListNpcs();
        void MakeSelf(oCNpc* npc);
        void Wait (oCNpc* npc);
        bool IsRunning() const { return m_Running; }
        bool IsNpcInMultilogue(oCNpc* npc) const { return m_Npcs.contains(npc->idx); }
        void EV_Finish();
        void EV_Next(int id);
        void Reset();
        void SetAutoTurn(bool autoTurn) { m_AutoTurn = autoTurn; }
        oCNpc* GetLastSelf() const { return m_LastSelf; }
        void AI_Output();
        void SetAutoMode(bool AutoMode) { m_AutoMode = AutoMode; }
        bool GetAutoMode() const { return m_AutoMode; }
        void SetAutoCam(bool AutoCam) { m_AutoCam = AutoCam; }
    };

    static zCMultilogue zMultilogue = zCMultilogue{}; // Global instance


    inline void zCMultilogue::AddNpc(oCNpc* npc)
    {
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogue::AddNpc");
        if (!npc) {
            log->Warning("Invalid NPC");
            return;
        }
        if (m_Npcs.contains(npc->idx)) {
            log->Warning("NPC with ID {0} already exists.", npc->idx);
            return;
        }
        if (Npc_IsInActiveVoblist(npc) && npc != GetDialogOwner() && npc != player) {
            npc->ClearEM();
        }
        if (npc != GetDialogOwner() && npc != player) {
            // StartAIState changes self so we back it up
            oCNpc* self = GetSelfInstance();
            npc->state.StartAIState("ZS_MULTILOGUE", 0, 0, 0, 0);
            parser->SetInstance("SELF", self);
        }
        m_Npcs[npc->idx] = npc;
        log->Info("NPC with ID {0} added.", npc->idx);
    }

    inline void zCMultilogue::Start()
    {
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogue::Start");
        if (m_Running) {
            log->Warning("Multilogue already running.");
            return;
        }
        if (!m_AutoMode) {
            m_AutoTurn = false;
        }
        m_LastSelf = GetDialogOwner();
        AddNpc(player);
        AddNpc(m_LastSelf);
        m_Running = true;
        Wait(m_LastSelf);
        log->Info("Starting {0}multilogue with {1} NPCs.", m_AutoMode ? "automatic " : "", m_Npcs.size());
        ListNpcs();
    }

    inline void zCMultilogue::Finish()
    {
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogue::Finish");
        if (!m_Running) {
            log->Warning("Multilogue not Running.");
            return;
        }
        if (!ogame->infoman) {
            log->Error("infoman not found.");
            return;
        }
        if (!GetDialogOwner()) {
            log->Error("dialog owner is invalid.");
            return;
        }

        MakeSelf(GetDialogOwner());

        // Idk if this is needed, but I don't want to touch it
        Wait (m_LastSelf);
        Wait (player);

        oCMsgManipulate* msg = new oCMsgManipulate( oCMsgManipulate::EV_EXCHANGE);
        msg->slot = "EV_FINISH";
        player->GetEM()->OnMessage(msg, player);
        m_AutoMode = false;
    }


    inline void zCMultilogue::EV_Finish() {
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogue::EV_Finish");
        if (!m_Running) {
            log->Warning("Multilogue has already finished.");
            return;
        }
        m_Running = false;
        m_LastSelf = nullptr;
        m_DistanceController.RestoreDistance();
        if (!GetDialogOwner()) {
            log->Error("dialog owner is invalid.");
            return;
        }
        for (auto& [key, npc] : m_Npcs) {
            if (npc && npc != player && npc != GetDialogOwner()) {
                npc->talkOther = nullptr;
                npc->state.StartRtnState(1); // Force routine exchange
            }
        }
        log->Info("Finishing multilogue with {0} NPCs.", m_Npcs.size());
        m_Npcs.clear();
    }


    inline void zCMultilogue::ListNpcs() {
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogue::ListNpcs");
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
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogue::Wait");
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
        static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogue::MakeSelf");
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
        if (npc != GetDialogOwner()) {
            Npc_FakeTalkState(npc);
        }
        Wait(npc);
        // Self and player will turn to each other if m_AutoTurn is enabled
        if (m_AutoTurn && !m_AutoMode) {
            m_LastSelf->GetEM()->OnMessage(new oCMsgMovement(oCMsgMovement::EV_TURNTOVOB, player), m_LastSelf);
            player->GetEM()->OnMessage(new oCMsgMovement(oCMsgMovement::EV_TURNTOVOB, m_LastSelf), player);
        }
    }

    inline void zCMultilogue::EV_Next(int id) {
        oCNpc* npc = m_Npcs.find(id)->second;
        if (npc) {
            static NH::Logger* log = NH::CreateLogger("zMul::zCMultilogue::EV_Next");
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
        m_DistanceController = zCDialogDistanceController{};
        m_LastSelf = nullptr;
        m_Npcs.clear();
        m_Running = false;
        m_AutoTurn = false;
        m_AutoMode = false;
        m_AutoCam = false;
    }

    inline void zCMultilogue::AI_Output()
    {
        zCParser* par = zCParser::GetParser();
        zSTRING name;
	    par->GetParameter(name);
        oCNpc* target = reinterpret_cast<oCNpc*>(par->GetInstance());
        oCNpc* talker = reinterpret_cast<oCNpc*>(par->GetInstance());
        if (target && talker) {
            if (!IsNpcInMultilogue(talker)) {
                AddNpc(talker);
            }
            if (!IsNpcInMultilogue(target)) {
                AddNpc(target);
            }
            if (!IsRunning()) {
                Start();
            }
            if (talker != player) {
                MakeSelf(talker);
            }
            if (m_AutoCam) {
                if (zMulCamera.GetMode() != zCMultilogueCamera::Mode::FULL) {
                    zMulCamera.SetModeInstant(zCMultilogueCamera::Mode::FULL);
                }
                zMulCamera.SetTarget(talker);
                zMulCamera.SetSource(target);
                zMulCamera.CameraEvent();
            }
            if (m_AutoTurn) {
                talker->GetEM()->OnMessage(new oCMsgMovement(oCMsgMovement::EV_TURNTOVOB, target), talker);
                target->GetEM()->OnMessage(new oCMsgMovement(oCMsgMovement::EV_TURNTOVOB, talker), target);
            }
            Wait(talker);
            oCMsgConversation* msg = new oCMsgConversation(oCMsgConversation::EV_OUTPUT, name);
            if (talker != player) {
                msg->target = player;
            }
            else {
                msg->target = target;
            }
            talker->GetEM()->OnMessage(msg, talker);
            Wait(talker);
        }
    };

}