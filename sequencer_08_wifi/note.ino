#define DRUM_LEVEL 150  // 128
#define DRUM_LEVEL_B 200
#define DRUM_NOISE_FREQ 100  // doesn't matter for white noise

#define HIHAT_FREQ1 100
#define HIHAT_FREQ2 128
#define HIHAT_FREQ3 256
#define HIHAT_FREQ4 384
#define HIHAT_FREQ5 512

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
    byte aNote = gSeqNotes[gSeqPatternIndex][gSeqNoteIndex];

    // 01 - kick
    if (aNote & D_KICK) {
        playDoubleEnvNote(&gMSynth[0]);
    }

    // 02 - snare
    if (aNote & D_SNARE) {
        playDoubleEnvNote(&gMSynth[1]);
    }

    // 04 - hihat
    if (aNote & D_HIHAT) {
        playSimpleEnvNote(&gMSynth[2]);
    }

    // 08 - clap
    if (aNote & D_CLAP) {
        playSimpleEnvNote(&gMSynth[3]);
    }

    // 16 - crash
    if (aNote & D_CRASH) {
        playSimpleEnvNote(&gMSynth[4]);
    }

    // 32 - tom hi
    if (aNote & D_TOMHI) {
        playDoubleEnvNote(&gMSynth[5]);
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

void assignTable(struct MDSynth* ptrSynth, const int8_t* table, int num_cells) {
    byte multi = MAX_NUM_CELLS / num_cells;
    for (int i = 0; i < num_cells; i++) {
        for (int x = 0; x < multi; x++) {
            ptrSynth->sMDOscTable[i * multi + x] = table[i];
        }
    }
    ptrSynth->sMDOsc.setTable(ptrSynth->sMDOscTable);
}

void setupNote(byte key, struct MDSynth* ptrSynth, const int8_t* table, int num_cells) {
    assignTable(ptrSynth, table, num_cells);
    ptrSynth->key = key;
}

void setupNotes() {
    setupNote(D_KICK, &gMSynth[0], SIN2048_DATA, SIN2048_NUM_CELLS);
    setupNote(D_SNARE, &gMSynth[1], SIN2048_DATA, SIN2048_NUM_CELLS);
    setupNote(D_HIHAT, &gMSynth[2], WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS);
    setupNote(D_CLAP, &gMSynth[3], WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS);
    setupNote(D_CRASH, &gMSynth[4], WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS);
    setupNote(D_TOMHI, &gMSynth[5], TRIANGLE2048_DATA, TRIANGLE2048_NUM_CELLS);

    gMSynth[0].sMFrequency = 45;  // (setting)
    gMSynth[0].sMAttackTime = 0;
    gMSynth[0].sMDecayTime = 0;
    gMSynth[0].sMSustainTime = 0;
    gMSynth[0].sMReleaseTime = 170;
    gMSynth[0].sMReleaseTimeP = 170;
    gMSynth[0].sMAttackLevel = DRUM_LEVEL_B;
    gMSynth[0].sMDecayLevel = DRUM_LEVEL_B;
    gMSynth[0].sMSustainLevel = DRUM_LEVEL_B;
    gMSynth[0].sMReleaseLevel = 0;
    //  gMSynth[0].sMFilterFrequency = 0;
    //  gMSynth[0].sMFilterResonance = 0;
    gMSynth[0].sMEnvSlope = 1;

    gMSynth[0].sMEnvA.setLevels(
        gMSynth[0].sMAttackLevel, gMSynth[0].sMDecayLevel,
        gMSynth[0].sMSustainLevel, gMSynth[0].sMReleaseLevel);
    gMSynth[0].sMEnvA.setTimes(
        gMSynth[0].sMAttackTime, gMSynth[0].sMDecayTime,
        gMSynth[0].sMSustainTime, gMSynth[0].sMReleaseTime);
    gMSynth[0].sMEnvP.setLevels(
        gMSynth[0].sMAttackLevel, gMSynth[0].sMDecayLevel,
        gMSynth[0].sMSustainLevel, gMSynth[0].sMReleaseLevel);
    gMSynth[0].sMEnvP.setTimes(
        gMSynth[0].sMAttackTime, gMSynth[0].sMDecayTime,
        gMSynth[0].sMSustainTime, gMSynth[0].sMReleaseTimeP);

    gMSynth[1].sMFrequency = 150;  // (setting)
    gMSynth[1].sMAttackTime = 0;
    gMSynth[1].sMDecayTime = 0;
    gMSynth[1].sMSustainTime = 0;
    gMSynth[1].sMReleaseTime = 160;  // (setting) 140-300
    gMSynth[1].sMReleaseTimeP = 140;
    gMSynth[1].sMAttackLevel = DRUM_LEVEL;
    gMSynth[1].sMDecayLevel = DRUM_LEVEL;
    gMSynth[1].sMSustainLevel = DRUM_LEVEL;
    gMSynth[1].sMReleaseLevel = 0;
    //  gMSynth[1].sMFilterFrequency = 0;
    //  gMSynth[1].sMFilterResonance = 0;
    gMSynth[1].sMEnvSlope = 1;

    gMSynth[1].sMEnvA.setLevels(
        gMSynth[1].sMAttackLevel, gMSynth[1].sMDecayLevel,
        gMSynth[1].sMSustainLevel, gMSynth[1].sMReleaseLevel);
    gMSynth[1].sMEnvA.setTimes(
        gMSynth[1].sMAttackTime, gMSynth[1].sMDecayTime,
        gMSynth[1].sMSustainTime, gMSynth[1].sMReleaseTime);
    gMSynth[1].sMEnvP.setLevels(
        gMSynth[1].sMAttackLevel, gMSynth[1].sMDecayLevel,
        gMSynth[1].sMSustainLevel, gMSynth[1].sMReleaseLevel);
    gMSynth[1].sMEnvP.setTimes(
        gMSynth[1].sMAttackTime, gMSynth[1].sMDecayTime,
        gMSynth[1].sMSustainTime, gMSynth[1].sMReleaseTimeP);

    // gMDOscSnareN.setFreq(DRUM_NOISE_FREQ);

    gMSynth[3].sMFrequency = 0;  // (only noise)
    gMSynth[3].sMAttackTime = 0;
    gMSynth[3].sMDecayTime = 0;
    gMSynth[3].sMSustainTime = 0;
    gMSynth[3].sMReleaseTime = 110;
    gMSynth[3].sMReleaseTimeP = 0;
    gMSynth[3].sMAttackLevel = DRUM_LEVEL;
    gMSynth[3].sMDecayLevel = DRUM_LEVEL;
    gMSynth[3].sMSustainLevel = DRUM_LEVEL;
    gMSynth[3].sMReleaseLevel = 0;
    //  gMSynth[3].sMFilterFrequency = 1200; // setting
    //  gMSynth[3].sMFilterResonance = 120;
    gMSynth[3].sMEnvSlope = 0;

    gMSynth[3].sMEnvA.setLevels(
        gMSynth[3].sMAttackLevel, gMSynth[3].sMDecayLevel,
        gMSynth[3].sMSustainLevel, gMSynth[3].sMReleaseLevel);
    gMSynth[3].sMEnvA.setTimes(
        gMSynth[3].sMAttackTime, gMSynth[3].sMDecayTime,
        gMSynth[3].sMSustainTime, gMSynth[3].sMReleaseTime);

    gMSynth[3].sMDOsc.setFreq(DRUM_NOISE_FREQ);

    gMSynth[2].sMFrequency = HIHAT_FREQ1;  // (only noise)
    gMSynth[2].sMAttackTime = 0;
    gMSynth[2].sMDecayTime = 0;
    gMSynth[2].sMSustainTime = 0;
    gMSynth[2].sMReleaseTime = 35;  // (settings)
    gMSynth[2].sMReleaseTimeP = 0;
    gMSynth[2].sMAttackLevel = DRUM_LEVEL;
    gMSynth[2].sMDecayLevel = DRUM_LEVEL;
    gMSynth[2].sMSustainLevel = DRUM_LEVEL;
    gMSynth[2].sMReleaseLevel = 0;
    //  gMSynth[2].sMFilterFrequency = 5000;
    //  gMSynth[2].sMFilterResonance = 60;
    gMSynth[2].sMEnvSlope = 0;

    gMSynth[2].sMEnvA.setLevels(
        gMSynth[2].sMAttackLevel, gMSynth[2].sMDecayLevel,
        gMSynth[2].sMSustainLevel, gMSynth[2].sMReleaseLevel);
    gMSynth[2].sMEnvA.setTimes(
        gMSynth[2].sMAttackTime, gMSynth[2].sMDecayTime,
        gMSynth[2].sMSustainTime, gMSynth[2].sMReleaseTime);

    gMSynth[2].sMDOsc.setFreq(gMSynth[2].sMFrequency);

    gMSynth[4].sMFrequency = 0;  // (only noise)
    gMSynth[4].sMAttackTime = 0;
    gMSynth[4].sMDecayTime = 0;
    gMSynth[4].sMSustainTime = 0;
    gMSynth[4].sMReleaseTime = 500;  // (setting)
    gMSynth[4].sMReleaseTimeP = 0;
    gMSynth[4].sMAttackLevel = DRUM_LEVEL;
    gMSynth[4].sMDecayLevel = DRUM_LEVEL;
    gMSynth[4].sMSustainLevel = DRUM_LEVEL;
    gMSynth[4].sMReleaseLevel = 0;
    gMSynth[4].sMEnvSlope = 0;

    gMSynth[4].sMEnvA.setLevels(
        gMSynth[4].sMAttackLevel, gMSynth[4].sMDecayLevel,
        gMSynth[4].sMSustainLevel, gMSynth[4].sMReleaseLevel);
    gMSynth[4].sMEnvA.setTimes(
        gMSynth[4].sMAttackTime, gMSynth[4].sMDecayTime,
        gMSynth[4].sMSustainTime, gMSynth[4].sMReleaseTime);

    gMSynth[4].sMDOsc.setFreq(DRUM_NOISE_FREQ);

    gMSynth[5].sMFrequency = 100;  // (setting)
    gMSynth[5].sMAttackTime = 0;
    gMSynth[5].sMDecayTime = 0;
    gMSynth[5].sMSustainTime = 0;
    gMSynth[5].sMReleaseTime = 200;
    gMSynth[5].sMReleaseTimeP = 200;
    gMSynth[5].sMAttackLevel = DRUM_LEVEL;
    gMSynth[5].sMDecayLevel = DRUM_LEVEL;
    gMSynth[5].sMSustainLevel = DRUM_LEVEL;
    gMSynth[5].sMReleaseLevel = 0;
    //  gMSynth[5].sMFilterFrequency = 0;
    //  gMSynth[5].sMFilterResonance = 0;
    gMSynth[5].sMEnvSlope = 1;

    gMSynth[5].sMEnvA.setLevels(
        gMSynth[5].sMAttackLevel, gMSynth[5].sMDecayLevel,
        gMSynth[5].sMSustainLevel, gMSynth[5].sMReleaseLevel);
    gMSynth[5].sMEnvA.setTimes(
        gMSynth[5].sMAttackTime, gMSynth[5].sMDecayTime,
        gMSynth[5].sMSustainTime, gMSynth[5].sMReleaseTime);
    gMSynth[5].sMEnvP.setLevels(
        gMSynth[5].sMAttackLevel, gMSynth[5].sMDecayLevel,
        gMSynth[5].sMSustainLevel, gMSynth[5].sMReleaseLevel);
    gMSynth[5].sMEnvP.setTimes(
        gMSynth[5].sMAttackTime, gMSynth[5].sMDecayTime,
        gMSynth[5].sMSustainTime, gMSynth[5].sMReleaseTimeP);
}

void updateEnvelopes() {
    gMSynth[0].sMEnvA.update();
    gMSynth[0].sMEnvP.update();
    gMSynth[0].sMDOsc.setFreq(
        gMSynth[0].sMFrequency +
        (gMSynth[0].sMEnvValueP >> gMSynth[0].sMEnvSlope));  // (setting)

    gMSynth[1].sMEnvA.update();
    gMSynth[1].sMEnvP.update();
    gMSynth[1].sMDOsc.setFreq(
        gMSynth[1].sMFrequency +
        (gMSynth[1].sMEnvValueP >> gMSynth[1].sMEnvSlope));  // (setting)

    gMSynth[2].sMEnvA.update();

    gMSynth[3].sMEnvA.update();

    gMSynth[4].sMEnvA.update();

    gMSynth[5].sMEnvA.update();
    gMSynth[5].sMEnvP.update();
    gMSynth[5].sMDOsc.setFreq(
        gMSynth[5].sMFrequency +
        (gMSynth[5].sMEnvValueP >> gMSynth[5].sMEnvSlope));  // (setting)
}

int updateAudioSeq() {
    gMSynth[0].sMEnvValueA = gMSynth[0].sMEnvA.next();
    gMSynth[0].sMEnvValueP = gMSynth[0].sMEnvP.next();
    gMSynth[1].sMEnvValueA = gMSynth[1].sMEnvA.next();
    gMSynth[1].sMEnvValueP = gMSynth[1].sMEnvP.next();
    gMSynth[2].sMEnvValueA = gMSynth[2].sMEnvA.next();
    gMSynth[3].sMEnvValueA = gMSynth[3].sMEnvA.next();
    gMSynth[4].sMEnvValueA = gMSynth[4].sMEnvA.next();
    gMSynth[5].sMEnvValueA = gMSynth[5].sMEnvA.next();
    gMSynth[5].sMEnvValueP = gMSynth[5].sMEnvP.next();

    return (int)(((gMSynth[0].sMEnvValueA * gMSynth[0].sMDOsc.next()) >> 1) +
                 ((gMSynth[1].sMEnvValueA * gMSynth[1].sMDOsc.next()) >>
                  2) +
                 ((gMSynth[2].sMEnvValueA * gMSynth[2].sMDOsc.next()) >>
                  1) +
                 ((gMSynth[3].sMEnvValueA * gMSynth[3].sMDOsc.next()) >> 1) +
                 ((gMSynth[5].sMEnvValueA * gMSynth[5].sMDOsc.next()) >>
                  1) +
                 ((gMSynth[4].sMEnvValueA * gMSynth[4].sMDOsc.next()) >>
                  2)) >>
           8;
}
