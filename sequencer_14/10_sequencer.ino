#define PHASE_A 1
#define PHASE_B 2
#define PHASE_C 4
#define PHASE_D 8
#define PHASE_E 16
#define PHASE_F 32

byte gSeqPhases[MAX_PATTERNS][STEP_COUNT] = {
    {PHASE_A, 0, 0, 0, PHASE_B, 0, 0, 0, PHASE_A, 0, 0, 0, PHASE_B, 0, 0, PHASE_A},
    {PHASE_A + PHASE_E, 0, PHASE_C, 0, PHASE_A, 0, PHASE_C, 0, PHASE_A, 0, PHASE_C,
     0, PHASE_D, 0, PHASE_C, PHASE_A},
    {PHASE_A, 0, 0, 0, PHASE_A, 0, 0, 0, PHASE_A, 0, 0, 0, PHASE_A, 0, 0, 0},
    {PHASE_F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

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