#define DRUM_LEVEL 150  // 128
#define DRUM_LEVEL_B 200
#define DRUM_NOISE_FREQ 100  // doesn't matter for white noise

#define HIHAT_FREQ1 100
#define HIHAT_FREQ2 128
#define HIHAT_FREQ3 256
#define HIHAT_FREQ4 384
#define HIHAT_FREQ5 512

#define MAX_NUM_CELLS 8192

// look at Phasemod_Envelope

typedef struct MDSynth {
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

MDSynth gMSynthKick;
MDSynth gMSynthSnare;
MDSynth gMSynthHihat;
MDSynth gMSynthClap;
MDSynth gMSynthCrash;
MDSynth gMSynthTomHi;

// Controller

unsigned int fnKick1Env(int val, int isInc) {
    gMSynthKick.sMEnvSlope = getVal(gMSynthKick.sMEnvSlope, val, isInc);
    return gMSynthKick.sMEnvSlope;
}

unsigned int fnKick1Freq(int val, int isInc) {
    // gMSynthKick.sMFrequency += (val * 5);
    gMSynthKick.sMFrequency = getVal(gMSynthKick.sMFrequency, val, isInc, 5);
    return gMSynthKick.sMFrequency;
}

unsigned int fnKick1ReleaseTime(int val, int isInc) {
    // gMSynthKick.sMReleaseTime += (val * 10);
    gMSynthKick.sMFrequency = getVal(gMSynthKick.sMReleaseTime, val, isInc, 10);
    gMSynthKick.sMEnvA.setReleaseTime(gMSynthKick.sMReleaseTime);
    return gMSynthKick.sMReleaseTime;
}

// Controller end

void playNote() {
    byte aNote = gSeqNotes[gSeqPatternIndex][gSeqNoteIndex];

    // 01 - kick
    if (aNote & D_KICK) {
        playDoubleEnvNote(&gMSynthKick);
    }

    // 02 - snare
    if (aNote & D_SNARE) {
        playDoubleEnvNote(&gMSynthSnare);
    }

    // 04 - hihat
    if (aNote & D_HIHAT) {
        playSimpleEnvNote(&gMSynthHihat);
    }

    // 08 - clap
    if (aNote & D_CLAP) {
        playSimpleEnvNote(&gMSynthClap);
    }

    // 16 - crash
    if (aNote & D_CRASH) {
        playSimpleEnvNote(&gMSynthCrash);
    }

    // 32 - tom hi
    if (aNote & D_TOMHI) {
        playDoubleEnvNote(&gMSynthTomHi);
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

void setupNotes() {
    assignTable(&gMSynthKick, SIN2048_DATA, SIN2048_NUM_CELLS);
    assignTable(&gMSynthSnare, SIN2048_DATA, SIN2048_NUM_CELLS);
    assignTable(&gMSynthHihat, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS);
    assignTable(&gMSynthClap, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS);
    assignTable(&gMSynthCrash, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS);
    assignTable(&gMSynthTomHi, TRIANGLE2048_DATA, TRIANGLE2048_NUM_CELLS);

    gMSynthKick.sMFrequency = 45;  // (setting)
    gMSynthKick.sMAttackTime = 0;
    gMSynthKick.sMDecayTime = 0;
    gMSynthKick.sMSustainTime = 0;
    gMSynthKick.sMReleaseTime = 170;
    gMSynthKick.sMReleaseTimeP = 170;
    gMSynthKick.sMAttackLevel = DRUM_LEVEL_B;
    gMSynthKick.sMDecayLevel = DRUM_LEVEL_B;
    gMSynthKick.sMSustainLevel = DRUM_LEVEL_B;
    gMSynthKick.sMReleaseLevel = 0;
    //  gMSynthKick.sMFilterFrequency = 0;
    //  gMSynthKick.sMFilterResonance = 0;
    gMSynthKick.sMEnvSlope = 1;

    gMSynthKick.sMEnvA.setLevels(
        gMSynthKick.sMAttackLevel, gMSynthKick.sMDecayLevel,
        gMSynthKick.sMSustainLevel, gMSynthKick.sMReleaseLevel);
    gMSynthKick.sMEnvA.setTimes(
        gMSynthKick.sMAttackTime, gMSynthKick.sMDecayTime,
        gMSynthKick.sMSustainTime, gMSynthKick.sMReleaseTime);
    gMSynthKick.sMEnvP.setLevels(
        gMSynthKick.sMAttackLevel, gMSynthKick.sMDecayLevel,
        gMSynthKick.sMSustainLevel, gMSynthKick.sMReleaseLevel);
    gMSynthKick.sMEnvP.setTimes(
        gMSynthKick.sMAttackTime, gMSynthKick.sMDecayTime,
        gMSynthKick.sMSustainTime, gMSynthKick.sMReleaseTimeP);

    gMSynthSnare.sMFrequency = 150;  // (setting)
    gMSynthSnare.sMAttackTime = 0;
    gMSynthSnare.sMDecayTime = 0;
    gMSynthSnare.sMSustainTime = 0;
    gMSynthSnare.sMReleaseTime = 160;  // (setting) 140-300
    gMSynthSnare.sMReleaseTimeP = 140;
    gMSynthSnare.sMAttackLevel = DRUM_LEVEL;
    gMSynthSnare.sMDecayLevel = DRUM_LEVEL;
    gMSynthSnare.sMSustainLevel = DRUM_LEVEL;
    gMSynthSnare.sMReleaseLevel = 0;
    //  gMSynthSnare.sMFilterFrequency = 0;
    //  gMSynthSnare.sMFilterResonance = 0;
    gMSynthSnare.sMEnvSlope = 1;

    gMSynthSnare.sMEnvA.setLevels(
        gMSynthSnare.sMAttackLevel, gMSynthSnare.sMDecayLevel,
        gMSynthSnare.sMSustainLevel, gMSynthSnare.sMReleaseLevel);
    gMSynthSnare.sMEnvA.setTimes(
        gMSynthSnare.sMAttackTime, gMSynthSnare.sMDecayTime,
        gMSynthSnare.sMSustainTime, gMSynthSnare.sMReleaseTime);
    gMSynthSnare.sMEnvP.setLevels(
        gMSynthSnare.sMAttackLevel, gMSynthSnare.sMDecayLevel,
        gMSynthSnare.sMSustainLevel, gMSynthSnare.sMReleaseLevel);
    gMSynthSnare.sMEnvP.setTimes(
        gMSynthSnare.sMAttackTime, gMSynthSnare.sMDecayTime,
        gMSynthSnare.sMSustainTime, gMSynthSnare.sMReleaseTimeP);

    // gMDOscSnareN.setFreq(DRUM_NOISE_FREQ);

    gMSynthClap.sMFrequency = 0;  // (only noise)
    gMSynthClap.sMAttackTime = 0;
    gMSynthClap.sMDecayTime = 0;
    gMSynthClap.sMSustainTime = 0;
    gMSynthClap.sMReleaseTime = 110;
    gMSynthClap.sMReleaseTimeP = 0;
    gMSynthClap.sMAttackLevel = DRUM_LEVEL;
    gMSynthClap.sMDecayLevel = DRUM_LEVEL;
    gMSynthClap.sMSustainLevel = DRUM_LEVEL;
    gMSynthClap.sMReleaseLevel = 0;
    //  gMSynthClap.sMFilterFrequency = 1200; // setting
    //  gMSynthClap.sMFilterResonance = 120;
    gMSynthClap.sMEnvSlope = 0;

    gMSynthClap.sMEnvA.setLevels(
        gMSynthClap.sMAttackLevel, gMSynthClap.sMDecayLevel,
        gMSynthClap.sMSustainLevel, gMSynthClap.sMReleaseLevel);
    gMSynthClap.sMEnvA.setTimes(
        gMSynthClap.sMAttackTime, gMSynthClap.sMDecayTime,
        gMSynthClap.sMSustainTime, gMSynthClap.sMReleaseTime);

    gMSynthClap.sMDOsc.setFreq(DRUM_NOISE_FREQ);

    gMSynthHihat.sMFrequency = HIHAT_FREQ1;  // (only noise)
    gMSynthHihat.sMAttackTime = 0;
    gMSynthHihat.sMDecayTime = 0;
    gMSynthHihat.sMSustainTime = 0;
    gMSynthHihat.sMReleaseTime = 35;  // (settings)
    gMSynthHihat.sMReleaseTimeP = 0;
    gMSynthHihat.sMAttackLevel = DRUM_LEVEL;
    gMSynthHihat.sMDecayLevel = DRUM_LEVEL;
    gMSynthHihat.sMSustainLevel = DRUM_LEVEL;
    gMSynthHihat.sMReleaseLevel = 0;
    //  gMSynthHihat.sMFilterFrequency = 5000;
    //  gMSynthHihat.sMFilterResonance = 60;
    gMSynthHihat.sMEnvSlope = 0;

    gMSynthHihat.sMEnvA.setLevels(
        gMSynthHihat.sMAttackLevel, gMSynthHihat.sMDecayLevel,
        gMSynthHihat.sMSustainLevel, gMSynthHihat.sMReleaseLevel);
    gMSynthHihat.sMEnvA.setTimes(
        gMSynthHihat.sMAttackTime, gMSynthHihat.sMDecayTime,
        gMSynthHihat.sMSustainTime, gMSynthHihat.sMReleaseTime);

    gMSynthHihat.sMDOsc.setFreq(gMSynthHihat.sMFrequency);

    gMSynthCrash.sMFrequency = 0;  // (only noise)
    gMSynthCrash.sMAttackTime = 0;
    gMSynthCrash.sMDecayTime = 0;
    gMSynthCrash.sMSustainTime = 0;
    gMSynthCrash.sMReleaseTime = 500;  // (setting)
    gMSynthCrash.sMReleaseTimeP = 0;
    gMSynthCrash.sMAttackLevel = DRUM_LEVEL;
    gMSynthCrash.sMDecayLevel = DRUM_LEVEL;
    gMSynthCrash.sMSustainLevel = DRUM_LEVEL;
    gMSynthCrash.sMReleaseLevel = 0;
    gMSynthCrash.sMEnvSlope = 0;

    gMSynthCrash.sMEnvA.setLevels(
        gMSynthCrash.sMAttackLevel, gMSynthCrash.sMDecayLevel,
        gMSynthCrash.sMSustainLevel, gMSynthCrash.sMReleaseLevel);
    gMSynthCrash.sMEnvA.setTimes(
        gMSynthCrash.sMAttackTime, gMSynthCrash.sMDecayTime,
        gMSynthCrash.sMSustainTime, gMSynthCrash.sMReleaseTime);

    gMSynthCrash.sMDOsc.setFreq(DRUM_NOISE_FREQ);

    gMSynthTomHi.sMFrequency = 100;  // (setting)
    gMSynthTomHi.sMAttackTime = 0;
    gMSynthTomHi.sMDecayTime = 0;
    gMSynthTomHi.sMSustainTime = 0;
    gMSynthTomHi.sMReleaseTime = 200;
    gMSynthTomHi.sMReleaseTimeP = 200;
    gMSynthTomHi.sMAttackLevel = DRUM_LEVEL;
    gMSynthTomHi.sMDecayLevel = DRUM_LEVEL;
    gMSynthTomHi.sMSustainLevel = DRUM_LEVEL;
    gMSynthTomHi.sMReleaseLevel = 0;
    //  gMSynthTomHi.sMFilterFrequency = 0;
    //  gMSynthTomHi.sMFilterResonance = 0;
    gMSynthTomHi.sMEnvSlope = 1;

    gMSynthTomHi.sMEnvA.setLevels(
        gMSynthTomHi.sMAttackLevel, gMSynthTomHi.sMDecayLevel,
        gMSynthTomHi.sMSustainLevel, gMSynthTomHi.sMReleaseLevel);
    gMSynthTomHi.sMEnvA.setTimes(
        gMSynthTomHi.sMAttackTime, gMSynthTomHi.sMDecayTime,
        gMSynthTomHi.sMSustainTime, gMSynthTomHi.sMReleaseTime);
    gMSynthTomHi.sMEnvP.setLevels(
        gMSynthTomHi.sMAttackLevel, gMSynthTomHi.sMDecayLevel,
        gMSynthTomHi.sMSustainLevel, gMSynthTomHi.sMReleaseLevel);
    gMSynthTomHi.sMEnvP.setTimes(
        gMSynthTomHi.sMAttackTime, gMSynthTomHi.sMDecayTime,
        gMSynthTomHi.sMSustainTime, gMSynthTomHi.sMReleaseTimeP);
}

void updateEnvelopes() {
    gMSynthKick.sMEnvA.update();
    gMSynthKick.sMEnvP.update();
    gMSynthKick.sMDOsc.setFreq(
        gMSynthKick.sMFrequency +
        (gMSynthKick.sMEnvValueP >> gMSynthKick.sMEnvSlope));  // (setting)

    gMSynthSnare.sMEnvA.update();
    gMSynthSnare.sMEnvP.update();
    gMSynthSnare.sMDOsc.setFreq(
        gMSynthSnare.sMFrequency +
        (gMSynthSnare.sMEnvValueP >> gMSynthSnare.sMEnvSlope));  // (setting)

    gMSynthHihat.sMEnvA.update();

    gMSynthClap.sMEnvA.update();

    gMSynthCrash.sMEnvA.update();

    gMSynthTomHi.sMEnvA.update();
    gMSynthTomHi.sMEnvP.update();
    gMSynthTomHi.sMDOsc.setFreq(
        gMSynthTomHi.sMFrequency +
        (gMSynthTomHi.sMEnvValueP >> gMSynthTomHi.sMEnvSlope));  // (setting)
}

int updateAudioSeq() {
    gMSynthKick.sMEnvValueA = gMSynthKick.sMEnvA.next();
    gMSynthKick.sMEnvValueP = gMSynthKick.sMEnvP.next();
    gMSynthSnare.sMEnvValueA = gMSynthSnare.sMEnvA.next();
    gMSynthSnare.sMEnvValueP = gMSynthSnare.sMEnvP.next();
    gMSynthHihat.sMEnvValueA = gMSynthHihat.sMEnvA.next();
    gMSynthClap.sMEnvValueA = gMSynthClap.sMEnvA.next();
    gMSynthCrash.sMEnvValueA = gMSynthCrash.sMEnvA.next();
    gMSynthTomHi.sMEnvValueA = gMSynthTomHi.sMEnvA.next();
    gMSynthTomHi.sMEnvValueP = gMSynthTomHi.sMEnvP.next();

    return (int)(((gMSynthKick.sMEnvValueA * gMSynthKick.sMDOsc.next()) >> 1) +
                 ((gMSynthSnare.sMEnvValueA * gMSynthSnare.sMDOsc.next()) >>
                  2) +
                 ((gMSynthHihat.sMEnvValueA * gMSynthHihat.sMDOsc.next()) >>
                  1) +
                 ((gMSynthClap.sMEnvValueA * gMSynthClap.sMDOsc.next()) >> 1) +
                 ((gMSynthTomHi.sMEnvValueA * gMSynthTomHi.sMDOsc.next()) >>
                  1) +
                 ((gMSynthCrash.sMEnvValueA * gMSynthCrash.sMDOsc.next()) >>
                  2)) >>
           8;
}
