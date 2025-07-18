META
{
    Parser    = Game;
    MergeMode = true;
};

func void ZS_MULTILOGUE() {
};

func int ZS_MULTILOGUE_Loop() {
    if (InfoManager_hasFinished()) {
        return LOOP_END;
    } else {
        return LOOP_CONTINUE;
    };
};

func void ZS_MULTILOGUE_End() {
};