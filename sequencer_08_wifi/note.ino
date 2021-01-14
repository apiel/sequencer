#define DRUM_LEVEL_B 200

#define MAX_NUM_CELLS 8192
#define SYNTH_COUNT 6

typedef struct MDSynth {
    byte key;
    bool isDoubleEnv;
    ADSR<CONTROL_RATE, AUDIO_RATE> sMEnvA;
    ADSR<CONTROL_RATE, AUDIO_RATE> sMEnvP;
    Oscil<MAX_NUM_CELLS, AUDIO_RATE> sMDOsc;
    int8_t sMDOscTable[MAX_NUM_CELLS];
    // settings
    int sMFrequency;
    unsigned int sMAttackTime;
    unsigned int sMDecayTime;
    unsigned int sMSustainTime;
    unsigned int sMReleaseTime;
    unsigned int sMReleaseTimeP;
    byte sMAttackLevel;
    byte sMDecayLevel;
    byte sMSustainLevel;
    byte sMReleaseLevel;
    //  unsigned int sMFilterFrequency;
    //  Q0n8 sMFilterResonance;
    byte sMEnvSlope;
    // state
    byte sMEnvValueA;
    byte sMEnvValueP;
};

MDSynth gMSynth[SYNTH_COUNT];

// Controller

unsigned int fnKick1Env(int val, int isInc) {
    gMSynth[0].sMEnvSlope = getVal(gMSynth[0].sMEnvSlope, val, isInc);
    return gMSynth[0].sMEnvSlope;
}

unsigned int fnKick1Freq(int val, int isInc) {
    // gMSynth[0].sMFrequency += (val * 5);
    gMSynth[0].sMFrequency = getVal(gMSynth[0].sMFrequency, val, isInc, 5);
    return gMSynth[0].sMFrequency;
}

unsigned int fnKick1ReleaseTime(int val, int isInc) {
    // gMSynth[0].sMReleaseTime += (val * 10);
    gMSynth[0].sMFrequency = getVal(gMSynth[0].sMReleaseTime, val, isInc, 10);
    gMSynth[0].sMEnvA.setReleaseTime(gMSynth[0].sMReleaseTime);
    return gMSynth[0].sMReleaseTime;
}

// Controller end

void playNote() {
    int aNote = gSeqNotes[gSeqPatternIndex][gSeqNoteIndex];

    for (int i = 0; i < SYNTH_COUNT; i++) {
        if (aNote & (int)pow(2, i)) {
            if (gMSynth[i].isDoubleEnv) {
                playDoubleEnvNote(&gMSynth[i]);
            } else {
                playSimpleEnvNote(&gMSynth[i]);
            }
        }
    }
}

void playSimpleEnvNote(struct MDSynth* ptrSynth) {
    ptrSynth->sMDOsc.setFreq(ptrSynth->sMFrequency);
    ptrSynth->sMEnvA.setReleaseTime(ptrSynth->sMReleaseTime);
    ptrSynth->sMEnvA.noteOn();
    ptrSynth->sMEnvA.noteOff();
}

void playDoubleEnvNote(struct MDSynth* ptrSynth) {
    ptrSynth->sMDOsc.setFreq(ptrSynth->sMFrequency);
    ptrSynth->sMEnvA.setReleaseTime(ptrSynth->sMReleaseTime);
    ptrSynth->sMEnvA.noteOn();
    ptrSynth->sMEnvP.noteOn();
    ptrSynth->sMEnvA.noteOff();
    ptrSynth->sMEnvP.noteOff();
}

void assignTable(byte key, const int8_t* table, int num_cells) {
    byte multi = MAX_NUM_CELLS / num_cells;
    for (int i = 0; i < num_cells; i++) {
        for (int x = 0; x < multi; x++) {
            gMSynth[key].sMDOscTable[i * multi + x] = table[i];
        }
    }
    gMSynth[key].sMDOsc.setTable(gMSynth[key].sMDOscTable);
}

void setupNote(byte key, const int8_t* table, int num_cells, bool isDoubleEnv,
               int frequency, unsigned int releaseTime,
               unsigned int releaseTimeP, byte envSlope) {
    assignTable(key, table, num_cells);
    gMSynth[key].isDoubleEnv = isDoubleEnv;
    gMSynth[key].sMFrequency = frequency;  // (setting)
    gMSynth[key].sMAttackTime = 0;
    gMSynth[key].sMDecayTime = 0;
    gMSynth[key].sMSustainTime = 0;
    gMSynth[key].sMReleaseTime = releaseTime;
    gMSynth[key].sMReleaseTimeP = releaseTimeP;
    gMSynth[key].sMAttackLevel = DRUM_LEVEL_B;
    gMSynth[key].sMDecayLevel = DRUM_LEVEL_B;
    gMSynth[key].sMSustainLevel = DRUM_LEVEL_B;
    gMSynth[key].sMReleaseLevel = 0;
    //  gMSynth[key].sMFilterFrequency = 0;
    //  gMSynth[key].sMFilterResonance = 0;
    gMSynth[key].sMEnvSlope = envSlope;

    gMSynth[key].sMEnvA.setLevels(
        gMSynth[key].sMAttackLevel, gMSynth[key].sMDecayLevel,
        gMSynth[key].sMSustainLevel, gMSynth[key].sMReleaseLevel);
    gMSynth[key].sMEnvA.setTimes(
        gMSynth[key].sMAttackTime, gMSynth[key].sMDecayTime,
        gMSynth[key].sMSustainTime, gMSynth[key].sMReleaseTime);
    gMSynth[key].sMEnvP.setLevels(
        gMSynth[key].sMAttackLevel, gMSynth[key].sMDecayLevel,
        gMSynth[key].sMSustainLevel, gMSynth[key].sMReleaseLevel);
    gMSynth[key].sMEnvP.setTimes(
        gMSynth[key].sMAttackTime, gMSynth[key].sMDecayTime,
        gMSynth[key].sMSustainTime, gMSynth[key].sMReleaseTimeP);
}

void setupNotes() {
    setupNote(0, SIN2048_DATA, SIN2048_NUM_CELLS, true, 45, 170, 170, 1);
    setupNote(1, SIN2048_DATA, SIN2048_NUM_CELLS, true, 150, 160, 140, 1);
    setupNote(2, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS, false, 100, 35,
              0, 0);
    setupNote(3, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS, false, 0, 110,
              0, 0);
    setupNote(4, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS, false, 0, 500,
              0, 0);
    setupNote(5, TRIANGLE2048_DATA, TRIANGLE2048_NUM_CELLS, true, 100, 200, 200,
              1);
}

void updateEnvelopes() {
    for (int i = 0; i < SYNTH_COUNT; i++) {
        if (gMSynth[i].isDoubleEnv) {
            gMSynth[i].sMEnvA.update();
            gMSynth[i].sMEnvP.update();
            gMSynth[i].sMDOsc.setFreq(
                gMSynth[i].sMFrequency +
                (gMSynth[i].sMEnvValueP >> gMSynth[i].sMEnvSlope));
        } else {
            gMSynth[i].sMEnvA.update();
        }
    }
}

int updateAudioSeq() {
    int ret = 0;
    for (int i = 0; i < SYNTH_COUNT; i++) {
        gMSynth[i].sMEnvValueA = gMSynth[i].sMEnvA.next();
        gMSynth[i].sMEnvValueP = gMSynth[i].sMEnvP.next();
        ret += (int)((gMSynth[i].sMEnvValueA * gMSynth[i].sMDOsc.next()) >> 1);
    }

    return ret >> 8;
}
