
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
/*
func void _Trialogue_SetCameraPtr (var int slfPtr, var int othPtr) {
    var oCNpc slf; slf = _^ (slfPtr);
    var oCNpc oth; oth = _^ (othPtr);

    //Setup override variable (has to be setup before calling oCNpc_ActivateDialogCam)
    trialogueOverrideCameraTarget = slfPtr;

    //Activate camera immediately
    if (oCNpc_ActivateDialogCam (oth, slf, FLOATNULL)) {
        var int aiPtr; aiPtr = zCSession_GetCameraAI ();
        zCAICamera_ReceiveMsg (aiPtr, _@ (zPLAYER_BEAMED));
    };
};

func void Trialogue_SetCamera (var int slfInstance, var int othInstance) {
    var oCNpc slf; slf = Hlp_GetNpc (slfInstance);
    var oCNpc oth; oth = Hlp_GetNpc (othInstance);

    Trialogue_Wait (slfInstance);

    AI_Function_II (hero, _Trialogue_SetCameraPtr, _@ (slf), _@ (oth));
};
*/