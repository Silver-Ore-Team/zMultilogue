namespace GOTHIC_NAMESPACE
{
    oCNpc* GetSelfInstance()
    {
        static NH::Logger* log = NH::CreateLogger("zMul::Helpers::GetSelfInstance");
        zCPar_Symbol* sym = parser->GetSymbol("SELF");
        if (sym) {
            oCNpc* self = dynamic_cast<oCNpc*>((zCVob*)sym->GetInstanceAdr());
            if (self) {
                return self;
            }
            log->Error("Failed to cast SELF to oCNpc.");
            return nullptr;
        }
        log->Error("Symbol SELF not found.");
        return nullptr;
    }

    bool Npc_IsInActiveVoblist(oCNpc* npc) {
        if (npc) {
            for (int i = 0; i < ogame->GetWorld()->activeVobList.numInArray; i++) {
                if (npc == dynamic_cast<oCNpc*>(ogame->GetWorld()->activeVobList[i])) {
                    return true;
                }
            }
            return false;
        }
        return false;
    }

    void AI_WaitTillEnd(oCNpc* self, oCNpc* other)
    {
        static NH::Logger* log = NH::CreateLogger("zMul::Helpers::AI_WaitTillEnd");
        if (!self || !other) {
            log->Warning("Invalid NPC instances.");
            return;
        }
        if(self->idx == other->idx) {
            //Imo this is not an error, no need to log it
            //log->Debug("Self and other are the same.");
            return;
        }
        // log->Trace("Synching {0} with {1}", self->idx, other->idx);
        oCMsgConversation* msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_WAITTILLEND,other);
        int nr = other -> GetEM()->GetNumMessages();
        zCEventMessage* watch = nullptr;
        for (int i = nr - 1; i >= 0; i--) {
            watch = other->GetEM()->GetEventMessage(i);
            if (!watch->IsOverlay()) {
                msg->watchMsg = watch;
                break;
            }
        }
        self->GetEM()->OnMessage(msg, self);
    }


    void Npc_FakeTalkState(oCNpc* npc) {
        if (npc) {
            npc->state.curState.valid = 1;
            npc->state.curState.index = parser->GetIndex("ZS_TALK");
            npc->state.curState.name = parser->GetSymbol("ZS_TALK")->name;
        }
    }

    zSTRING GetVobString(zCVob* vob)
    {
        if (vob) {
            zSTRING info;
            oCNpc* npc = dynamic_cast<oCNpc*>(vob);
            if (npc) {
                info += "Npc ID: ";
                info += npc->idx;
            }
            else {
                info += "Vob: ";
                info += vob->objectName;;
            }    
            return info;
        }
        return "nullptr";
    }
    
    oCNpc* GetDialogOwner()
    {
        static oCInformationManager& mgrInfos = oCInformationManager::GetInformationManager();
        if (mgrInfos.HasFinished()) {
            return nullptr;
        }
        if (mgrInfos.Npc) {
            return mgrInfos.Npc;
        }
        return nullptr;
    }
};