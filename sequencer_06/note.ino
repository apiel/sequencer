#define DRUM_LEVEL 150  // 128
#define DRUM_LEVEL_B 200
#define DRUM_NOISE_FREQ 100  // doesn't matter for white noise

#define HIHAT_FREQ1 100
#define HIHAT_FREQ2 128
#define HIHAT_FREQ3 256
#define HIHAT_FREQ4 384
#define HIHAT_FREQ5 512

// look at Phasemod_Envelope

typedef struct {
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
} MDSynth;

MDSynth gMSynthKick;
MDSynth gMSynthSnare;
MDSynth gMSynthHihat;
MDSynth gMSynthClap;
MDSynth gMSynthCrash;
MDSynth gMSynthTomHi;

// oscillators
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> gMDOscKick(SIN2048_DATA);
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> gMDOscSnare(SIN2048_DATA);
Oscil<WHITENOISE8192_NUM_CELLS, AUDIO_RATE> gMDOscSnareN(WHITENOISE8192_DATA);
Oscil<WHITENOISE8192_NUM_CELLS, AUDIO_RATE> gMDOscHihatN(WHITENOISE8192_DATA);
Oscil<WHITENOISE8192_NUM_CELLS, AUDIO_RATE> gMDOscClapN(WHITENOISE8192_DATA);
Oscil<WHITENOISE8192_NUM_CELLS, AUDIO_RATE> gMDOscCrashN(WHITENOISE8192_DATA);
Oscil<TRIANGLE2048_NUM_CELLS, AUDIO_RATE> gMDOscTomHi(TRIANGLE2048_DATA);

// envelopes
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvKickA;
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvKickP;
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvSnareA;
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvSnareP;
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvHihatA;
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvClapA;
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvCrashA;
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvTomHiA;
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvTomHiP;

// Controller

unsigned int fnKick1Env(int val) {
    gMSynthKick.sMEnvSlope += val;
    return gMSynthKick.sMEnvSlope;
}

unsigned int fnKick1Freq(int val) {
    gMSynthKick.sMFrequency += (val * 5);
    return gMSynthKick.sMFrequency;
}

unsigned int fnKick1ReleaseTime(int val) {
    gMSynthKick.sMReleaseTime += (val * 10);
    gMEnvKickA.setReleaseTime(gMSynthKick.sMReleaseTime);
    return gMSynthKick.sMReleaseTime;
}

// Controller end

void playNote() {
    byte aNote = gSeqNotes[gSeqPatternIndex][gSeqNoteIndex];

    // 01 - kick
    if (aNote & D_KICK) {
        playDKick();
    }

    // 02 - snare
    if (aNote & D_SNARE) {
        playDSnare();
    }

    // 04 - hihat
    if (aNote & D_HIHAT) {
        playDHihat();
    }

    // 08 - clap
    if (aNote & D_CLAP) {
        playDClap();
    }

    // 16 - crash
    if (aNote & D_CRASH) {
        playDCrash();
    }

    // 32 - tom hi
    if (aNote & D_TOMHI) {
        playDTomHi();
    }
}

void playDKick() {
    gMDOscKick.setFreq(gMSynthKick.sMFrequency);
    gMEnvKickA.noteOn();
    gMEnvKickP.noteOn();
    gMEnvKickA.noteOff();
    gMEnvKickP.noteOff();
}

void playDSnare() {
    gMDOscSnare.setFreq(gMSynthSnare.sMFrequency);
    gMEnvSnareA.noteOn();
    gMEnvSnareP.noteOn();
    gMEnvSnareA.noteOff();
    gMEnvSnareP.noteOff();
}

void playDHihat() {
    gMEnvHihatA.setReleaseTime(gMSynthHihat.sMReleaseTime);
    gMEnvHihatA.noteOn();
    gMEnvHihatA.noteOff();
}

void playDHihatO() {
    gMEnvHihatA.setReleaseTime(gMSynthHihat.sMReleaseTime >> 1);
    gMEnvHihatA.noteOn();
    gMEnvHihatA.noteOff();
}

void playDClap() {
    gMEnvClapA.noteOn();
    gMEnvClapA.noteOff();
}

void playDCrash() {
    gMEnvCrashA.noteOn();
    gMEnvCrashA.noteOff();
}

void playDTomHi() {
    gMDOscTomHi.setFreq(gMSynthTomHi.sMFrequency);
    gMEnvTomHiA.noteOn();
    gMEnvTomHiP.noteOn();
    gMEnvTomHiA.noteOff();
    gMEnvTomHiP.noteOff();
}

void playDTomLo() {
    gMDOscTomHi.setFreq(gMSynthTomHi.sMFrequency << 1);
    gMEnvTomHiA.noteOn();
    gMEnvTomHiP.noteOn();
    gMEnvTomHiA.noteOff();
    gMEnvTomHiP.noteOff();
}

void setupNotes() {
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

    gMEnvKickA.setLevels(gMSynthKick.sMAttackLevel, gMSynthKick.sMDecayLevel,
                         gMSynthKick.sMSustainLevel,
                         gMSynthKick.sMReleaseLevel);
    gMEnvKickA.setTimes(gMSynthKick.sMAttackTime, gMSynthKick.sMDecayTime,
                        gMSynthKick.sMSustainTime, gMSynthKick.sMReleaseTime);
    gMEnvKickP.setLevels(gMSynthKick.sMAttackLevel, gMSynthKick.sMDecayLevel,
                         gMSynthKick.sMSustainLevel,
                         gMSynthKick.sMReleaseLevel);
    gMEnvKickP.setTimes(gMSynthKick.sMAttackTime, gMSynthKick.sMDecayTime,
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

    gMEnvSnareA.setLevels(gMSynthSnare.sMAttackLevel, gMSynthSnare.sMDecayLevel,
                          gMSynthSnare.sMSustainLevel,
                          gMSynthSnare.sMReleaseLevel);
    gMEnvSnareA.setTimes(gMSynthSnare.sMAttackTime, gMSynthSnare.sMDecayTime,
                         gMSynthSnare.sMSustainTime,
                         gMSynthSnare.sMReleaseTime);
    gMEnvSnareP.setLevels(gMSynthSnare.sMAttackLevel, gMSynthSnare.sMDecayLevel,
                          gMSynthSnare.sMSustainLevel,
                          gMSynthSnare.sMReleaseLevel);
    gMEnvSnareP.setTimes(gMSynthSnare.sMAttackTime, gMSynthSnare.sMDecayTime,
                         gMSynthSnare.sMSustainTime,
                         gMSynthSnare.sMReleaseTimeP);

    gMDOscSnareN.setFreq(DRUM_NOISE_FREQ);

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

    gMEnvClapA.setLevels(gMSynthClap.sMAttackLevel, gMSynthClap.sMDecayLevel,
                         gMSynthClap.sMSustainLevel,
                         gMSynthClap.sMReleaseLevel);
    gMEnvClapA.setTimes(gMSynthClap.sMAttackTime, gMSynthClap.sMDecayTime,
                        gMSynthClap.sMSustainTime, gMSynthClap.sMReleaseTime);

    gMDOscClapN.setFreq(DRUM_NOISE_FREQ);

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

    gMEnvHihatA.setLevels(gMSynthHihat.sMAttackLevel, gMSynthHihat.sMDecayLevel,
                          gMSynthHihat.sMSustainLevel,
                          gMSynthHihat.sMReleaseLevel);
    gMEnvHihatA.setTimes(gMSynthHihat.sMAttackTime, gMSynthHihat.sMDecayTime,
                         gMSynthHihat.sMSustainTime,
                         gMSynthHihat.sMReleaseTime);

    gMDOscHihatN.setFreq(gMSynthHihat.sMFrequency);

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

    gMEnvCrashA.setLevels(gMSynthCrash.sMAttackLevel, gMSynthCrash.sMDecayLevel,
                          gMSynthCrash.sMSustainLevel,
                          gMSynthCrash.sMReleaseLevel);
    gMEnvCrashA.setTimes(gMSynthCrash.sMAttackTime, gMSynthCrash.sMDecayTime,
                         gMSynthCrash.sMSustainTime,
                         gMSynthCrash.sMReleaseTime);

    gMDOscCrashN.setFreq(DRUM_NOISE_FREQ);

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

    gMEnvTomHiA.setLevels(gMSynthTomHi.sMAttackLevel, gMSynthTomHi.sMDecayLevel,
                          gMSynthTomHi.sMSustainLevel,
                          gMSynthTomHi.sMReleaseLevel);
    gMEnvTomHiA.setTimes(gMSynthTomHi.sMAttackTime, gMSynthTomHi.sMDecayTime,
                         gMSynthTomHi.sMSustainTime,
                         gMSynthTomHi.sMReleaseTime);
    gMEnvTomHiP.setLevels(gMSynthTomHi.sMAttackLevel, gMSynthTomHi.sMDecayLevel,
                          gMSynthTomHi.sMSustainLevel,
                          gMSynthTomHi.sMReleaseLevel);
    gMEnvTomHiP.setTimes(gMSynthTomHi.sMAttackTime, gMSynthTomHi.sMDecayTime,
                         gMSynthTomHi.sMSustainTime,
                         gMSynthTomHi.sMReleaseTimeP);
}

void updateEnvelopes() {
    gMEnvKickA.update();
    gMEnvKickP.update();
    gMDOscKick.setFreq(
        gMSynthKick.sMFrequency +
        (gMSynthKick.sMEnvValueP >> gMSynthKick.sMEnvSlope));  // (setting)

    gMEnvSnareA.update();
    gMEnvSnareP.update();
    gMDOscSnare.setFreq(
        gMSynthSnare.sMFrequency +
        (gMSynthSnare.sMEnvValueP >> gMSynthSnare.sMEnvSlope));  // (setting)

    gMEnvHihatA.update();

    gMEnvClapA.update();

    gMEnvCrashA.update();

    gMEnvTomHiA.update();
    gMEnvTomHiP.update();
    gMDOscTomHi.setFreq(
        gMSynthTomHi.sMFrequency +
        (gMSynthTomHi.sMEnvValueP >> gMSynthTomHi.sMEnvSlope));  // (setting)
}

int updateAudioSeq() {
    gMSynthKick.sMEnvValueA = gMEnvKickA.next();
    gMSynthKick.sMEnvValueP = gMEnvKickP.next();
    gMSynthSnare.sMEnvValueA = gMEnvSnareA.next();
    gMSynthSnare.sMEnvValueP = gMEnvSnareP.next();
    gMSynthHihat.sMEnvValueA = gMEnvHihatA.next();
    gMSynthClap.sMEnvValueA = gMEnvClapA.next();
    gMSynthCrash.sMEnvValueA = gMEnvCrashA.next();
    gMSynthTomHi.sMEnvValueA = gMEnvTomHiA.next();
    gMSynthTomHi.sMEnvValueP = gMEnvTomHiP.next();

    return (int)(((gMSynthKick.sMEnvValueA * gMDOscKick.next()) >> 1) +
                 ((gMSynthSnare.sMEnvValueA *
                       (gMDOscSnare.next() + gMDOscSnareN.next()) >>
                   2)) +
                 ((gMSynthHihat.sMEnvValueA * gMDOscHihatN.next()) >> 1) +
                 ((gMSynthClap.sMEnvValueA * gMDOscClapN.next()) >> 1) +
                 ((gMSynthTomHi.sMEnvValueA * gMDOscTomHi.next()) >> 1) +
                 ((gMSynthCrash.sMEnvValueA * gMDOscCrashN.next()) >> 2)) >>
           8;
}
