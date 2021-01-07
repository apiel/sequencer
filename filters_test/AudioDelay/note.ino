#include <AudioDelay.h>

// 128/16384 seconds * 340.29 m/s speed of sound = 3.5 metres
AudioDelay<128> aLoopDel0;
AudioDelay<128, int> aLoopDel1;
AudioDelay<256, int> aLoopDel2;  // 7 metres
AudioDelay<512, int> aLoopDel3;

int8_t early_reflection1 = 37;
int8_t early_reflection2 = 77;
int8_t early_reflection3 = 127;
int8_t loop1_delay = 117;
uint8_t loop2_delay = 255;
uint8_t loop3_delay = 511;
int8_t feedback_level = 85;

// new

#define DRUM_LEVEL 200

int sMFrequency = 45;  // (setting)
unsigned int sMAttackTime = 0;
unsigned int sMDecayTime = 0;
unsigned int sMSustainTime = 0;
unsigned int sMReleaseTime = 170;
unsigned int sMReleaseTimeP = 170;
byte sMAttackLevel = DRUM_LEVEL;
byte sMDecayLevel = DRUM_LEVEL;
byte sMSustainLevel = DRUM_LEVEL;
byte sMReleaseLevel = 0;
byte sMFilterFrequency = 0;
byte sMFilterResonance = 0;
byte sMEnvSlope = 1;
byte sMEnvValueA;
byte sMEnvValueP;

// oscillators
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> gMDOscKick(SIN2048_DATA);

// envelopes
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvKickA;
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvKickP;

void playNote() {
    byte aNote = gSeqNotes[gSeqNoteIndex];

    // 01 - kick
    if (aNote & D_KICK) {
        playDKick();
    }
}

void playDKick() {
    gMDOscKick.setFreq(sMFrequency);
    gMEnvKickA.noteOn();
    gMEnvKickP.noteOn();
    gMEnvKickA.noteOff();
    gMEnvKickP.noteOff();
}

void setupNotes() {
    aLoopDel1.set(loop1_delay);
    aLoopDel2.set(loop2_delay);
    aLoopDel3.set(loop3_delay);

    gMEnvKickA.setLevels(sMAttackLevel, sMDecayLevel, sMSustainLevel,
                         sMReleaseLevel);
    gMEnvKickA.setTimes(sMAttackTime, sMDecayTime, sMSustainTime,
                        sMReleaseTime);
    gMEnvKickP.setLevels(sMAttackLevel, sMDecayLevel, sMSustainLevel,
                         sMReleaseLevel);
    gMEnvKickP.setTimes(sMAttackTime, sMDecayTime, sMSustainTime,
                        sMReleaseTimeP);
}

void updateEnvelopes() {
    gMEnvKickA.update();
    gMEnvKickP.update();
    gMDOscKick.setFreq(sMFrequency + (sMEnvValueP >> sMEnvSlope));  // (setting)
}

int recycle1, recycle2;  // new

int updateAudioSeq() {
    sMEnvValueA = gMEnvKickA.next();
    sMEnvValueP = gMEnvKickP.next();

    int kickSound = (int)(((sMEnvValueA * gMDOscKick.next()) >> 1)) >> 8;

    // return kickSound;

    // new

    // early reflections
    int asig = aLoopDel0.next(kickSound, early_reflection1);
    asig += aLoopDel0.read(early_reflection2);
    asig += aLoopDel0.read(early_reflection3);
    asig >>= 2;

    // // recirculating delays
    int8_t feedback_sig1 = (recycle1 * feedback_level) >> 7;
    int8_t feedback_sig2 = (recycle2 * feedback_level) >> 7;
    int sig3 = aLoopDel1.next(asig + feedback_sig1);
    int sig4 = aLoopDel3.next(asig + feedback_sig2);
    recycle1 = sig3 + sig4;
    recycle2 = sig3 - sig4;

    return kickSound + (recycle1 >> 2);
}
