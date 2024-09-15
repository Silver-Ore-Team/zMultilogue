namespace GOTHIC_NAMESPACE
{
    oCNpc* GetSelfInstance()
    {
        static NH::Logger* log = NH::CreateLogger("GetSelfInstance");
        zCPar_Symbol* sym = parser->GetSymbol("SELF");
        if (sym) {
            oCNpc* self = dynamic_cast<oCNpc*>((zCVob*)sym->GetInstanceAdr());
            if (self) {
                return self;
            }
            else {
                log->Error("Failed to cast SELF to oCNpc.");
                return nullptr;
            }
        }
        else {
            log->Error("Symbol SELF not found.");
            return nullptr;
        }
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
        if (self && other) {
            oCMsgConversation* msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_WAITTILLEND,other);
            int nr = other -> GetEM()->GetNumMessages();
            zCEventMessage* watch = NULL;
            for (int i=nr-1; i>=0; i--) {
                watch = other->GetEM()->GetEventMessage(i);
                if (!watch->IsOverlay()) {
                    msg->watchMsg = watch;
                    break;
                }
            }
            self -> GetEM() -> OnMessage(msg ,self);
        }
    }


};