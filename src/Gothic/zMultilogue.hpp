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
    };

    zCMultilogue::zCMultilogue()
    {
        // cameraAdapter =
    }

    zCMultilogue::~zCMultilogue()
    {
        // delete cameraAdapter;
    }

    void zCMultilogue::AddNpc(oCNpc* npc)
    {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::AddNpc");
        if (npc) {
            if (npcs.contains(npc->idx)) {
                log->Warning("NPC with ID {0} already exists.", npc->idx);
            } else {
                // if (Npc_IsInActiveVoblist(npc)) {
                //     npc->ClearEM();
                // }
                // oCNpc* slef = GetSelfInstance();
                // npc->state.StartAIState("ZS_MULTILOGUE", 0, 0, 0, 0);
                // parser->SetInstance("SELF", slef);
                npcs[npc->idx] = npc;
            }
            // comment later
            ListNpcs();

        }
        else {
            log->Error("Invalid NPC");
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
            // log->Info("Finishing multilogue with {0} NPCs.", npcs.size());
            // oCInformationManager informatonManager = oCInformationManager::GetInformationManager();
            // if (!ogame->infoman)    { return; }
            // if (!informatonManager.Npc) { return; }
            // if (!informatonManager.Player) { return; }
            //
            // oCNpc* slf = informatonManager.Npc;
            // oCNpc* oth = informatonManager.Player;
            //
            // AI_WaitTillEnd(slf, oth);
            // AI_WaitTillEnd(oth, slf);
            //
            // Wait (slf);
            // Wait (oth);

            //Event Finish
        }
    }

    inline void zCMultilogue::ListNpcs() {
        static NH::Logger* log = NH::CreateLogger("zCMultilogue::ListNpcs");
        for (auto& [key, value] : npcs) {
            log->Info("NPC ID: {0}", key);
        }
    }

    // void zCMultilogue::Wait(oCNpc* npc)
    // {
    //
    //     AI_WaitTillEnd(lastSelf, npc);
    //     AI_WaitTillEnd(npc, lastSelf);
    //
    //     //Sync hero with new npc & npc with hero
    //     AI_WaitTillEnd(player, npc);
    //     AI_WaitTillEnd(npc, player);
    //
    //     //Sync all Npcs invited to trialogue
    //     oCNpc* lastNpc;
    //     oCNpc* nextNpc;
    //
    //     lastNpc = npcs[0];
    //
    //     for (auto & npc : npcs) {
    //         nextNpc = npc.second;
    //         if (lastNpc && nextNpc) {
    //             AI_WaitTillEnd(nextNpc, lastNpc);
    //             lastNpc = nextNpc;
    //         }
    //     }
    // }

    // void zCMultilogue::MakeSelf(oCNpc *npc) {
    //     if (npc) {
    //         Wait(npc);
    //         lastSelf = npc;
    //         // Event next
    //     }
    // }


    zCMultilogue* zMultilogue = nullptr; // Global instance
}