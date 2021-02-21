#define D_KICK 1
#define D_SNARE 2
#define D_HIHAT 4
#define D_CLAP 8
#define D_CRASH 16
#define D_PHASOR 32

byte gSeqPhases[MAX_PATTERNS][STEP_COUNT] = {
    {D_KICK, 0, 0, 0, D_SNARE, 0, 0, 0, D_KICK, 0, 0, 0, D_SNARE, 0, 0, D_KICK},
    {D_KICK + D_CRASH, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT,
     0, D_CLAP, 0, D_HIHAT, D_KICK},
    {D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0},
    {D_PHASOR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

byte gCurrentPattern[STEP_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0};

void playPhase() {
    int aPhase = gCurrentPattern[gSeqStepIndex];

    for (int i = 0; i < MAX_PHASES; i++) {
        if (aPhase & (int)pow(2, i)) {
            phases[i].noteOn(gSeqStepIndex);
        }
    }
}

// Actions

void togglePhase(byte phaseIdx, byte pos) {
    int aPhase = gCurrentPattern[pos];
    int powPhase = pow(2, phaseIdx);
    if (aPhase & powPhase) {
        gCurrentPattern[pos] -= powPhase;
    } else {
        gCurrentPattern[pos] += powPhase;
    }
}

void setStepPattern(byte step, int val) { gCurrentPattern[step] = val; }

void assignCurrentPattern(byte index) {
    gCurrentPatternId = index % MAX_PATTERNS;
    for (int i = 0; i < STEP_COUNT; i++) {
        gCurrentPattern[i] = gSeqPhases[gCurrentPatternId][i];
    }
}