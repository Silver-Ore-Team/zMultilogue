#include <unordered_map>

namespace GOTHIC_NAMESPACE
{
    class zCMultilogue
    {
    private:
        zCMultilogueCameraAdapter* cameraAdapter;
        oCNpc* lastSelf;
        std::unordered_map<int, oCNpc*> npcs;
        bool running = false;
    public:
        zCMultilogue();
        ~zCMultilogue();
        void AddNpc(oCNpc* npc);
        void Start();
        void Finish();
        void ListNpcs();
        void MakeSelf(oCNpc* npc);
        void Wait (oCNpc* npc);
        bool IsRunning() { return running; }
        zCMultilogueCameraAdapter* GetCameraAdapter() { return cameraAdapter; }
        void EV_Finish();
        void EV_Next(int id);
    };

    zCMultilogue* zMultilogue = nullptr; // Global instance

    zCMultilogue::zCMultilogue()
    {
        cameraAdapter = new zCMultilogueCameraAdapter();
    }

    zCMultilogue::~zCMultilogue()
    {
        delete cameraAdapter;
    }

    void zCMultilogue::AddNpc(oCNpc* npc)
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::AddNpc");
        if (npc) {
            if (npcs.contains(npc->idx)) {
                log->Warning("NPC with ID {0} already exists.", npc->idx);
            } else {
                if (Npc_IsInActiveVoblist(npc)) {
                    npc->ClearEM();
                }
                oCNpc* self = GetSelfInstance();
                npc->state.StartAIState("ZS_MULTILOGUE", 0, 0, 0, 0);
                parser->SetInstance("SELF", self);
                npcs[npc->idx] = npc;
            }
            // comment later
            ListNpcs();

        }
        else {
            log->Warning("Invalid NPC");
        }
    }

    void zCMultilogue::Start()
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::Start");
        if (running) {
            log->Warning("Multilogue already running.");
            return;
        }
        else {
            oCNpc* self = GetSelfInstance();
            if (!self) {
                log->Error("Failed to get SELF instance.");
                return;
            }
            lastSelf = self;
            AddNpc(self);
            AddNpc(player);
            running = true;
            log->Info("Starting multilogue with {0} NPCs.", npcs.size());

            Npc_FakeTalkState(GetSelfInstance());
        }
    }

    void zCMultilogue::Finish()
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::Finish");
        if (!running) {
            log->Warning("Multilogue not running.");
            return;
        }
        else {
            static oCInformationManager& mgrInfos = oCInformationManager::GetInformationManager();
            if (!ogame->infoman)    { return; }
            if (!mgrInfos.Npc) { return; }
            if (!mgrInfos.Player) { return; }

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

            lastSelf->GetEM()->OnMessage( new oCMsgConversation( oCMsgConversation::EV_PROCESSINFOS), player );
        }
    }

    void zCMultilogue::EV_Finish() {
        if (!running) {
            return;
        }
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::EV_Finish");
        running = false;
        log->Info("Finishing multilogue with {0} NPCs.", npcs.size());

        delete this;
        zMultilogue = nullptr;
    }

    inline void zCMultilogue::ListNpcs() {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::ListNpcs");
        log->Trace("Listing NPCs:");
        for (auto& [key, value] : npcs) {
            log->Trace("NPC ID: {0}", key);
        }
    }

    void zCMultilogue::Wait(oCNpc* npc)
    {
        if (npc) {
            static NH::Logger* log = NH::CreateLogger("zCMultilogue::Wait");
            if (!npcs.contains(npc->idx)) {
                log->Warning("NPC with ID {0} is not in the multilogue", npc->idx);
                return;
            }
            AI_WaitTillEnd(lastSelf, npc);
            AI_WaitTillEnd(npc, lastSelf);

            //Sync hero with new npc & npc with hero
            AI_WaitTillEnd(player, npc);
            AI_WaitTillEnd(npc, player);

            //Sync all Npcs invited to trialogue
            oCNpc* lastNpc;
            oCNpc* nextNpc;

            lastNpc = npcs[0];

            for (auto & npc : npcs) {
                nextNpc = npc.second;
                if (lastNpc && nextNpc) {
                    AI_WaitTillEnd(nextNpc, lastNpc);
                    lastNpc = nextNpc;
                }
            }
        }
    }

    void zCMultilogue::MakeSelf(oCNpc *npc) {
        if (npc) {
            static NH::Logger* log = NH::CreateLogger("zCMultilogue::MakeSelf");
            if (!npcs.contains(npc->idx)) {
                log->Warning("NPC with ID {0} is not in the multilogue", npc->idx);
                return;
            }
            Wait(npc);
            lastSelf = npc;
            oCMsgManipulate* msg = new oCMsgManipulate( oCMsgManipulate::EV_EXCHANGE);
            msg->slot = "EV_NEXT";
            msg->flag = npc->idx;
            player->GetEM()->OnMessage(msg, player);
            parser->SetInstance("SELF", lastSelf);

            Npc_FakeTalkState(npc);
        }
    }

    void zCMultilogue::EV_Next(int id) {
        oCNpc* npc = npcs[id];
        if (npc) {
            static NH::Logger* log = NH::CreateLogger("zCMultilogue::EV_Next");
            log -> Info("Next NPC: {0}", id);
            npc->talkOther = nullptr;

            cameraAdapter->SetTarget(npc);
        }
    }

}