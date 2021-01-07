#include <ADSR.h>
#include <mozzi_rand.h>

ADSR<AUDIO_RATE, AUDIO_RATE> envelope;

unsigned int duration, attack, decay, sustain, release_ms;

// new

#define DRUM_LEVEL 200

int sMFrequency = 45;  // (setting)
unsigned int sMAttackTime = 0;
unsigned int sMDecayTime = 0;
unsigned int sMSustainTime = 100;
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

    // new

    // choose envelope levels
      byte attack_level = rand(128)+127;
      byte decay_level = rand(255);
    envelope.setADLevels(attack_level, decay_level);
    // gMEnvKickP.setADLevels(attack_level, decay_level);

    // generate a random new adsr time parameter value in milliseconds
    unsigned int new_value = rand(300) +100;
    Serial.println(new_value);
    // randomly choose one of the adsr parameters and set the new value
    switch (rand(4)) {
        case 0:
            attack = new_value;
            break;

        case 1:
            decay = new_value;
            break;

        case 2:
            sustain = new_value;
            break;

        case 3:
            release_ms = new_value;
            break;
    }
    envelope.setTimes(attack, decay, sustain, release_ms);
    // gMEnvKickP.setTimes(attack, decay, sustain, release_ms);
    envelope.noteOn();
    envelope.noteOff();
}

int updateAudioSeq() {
    sMEnvValueA = gMEnvKickA.next();
    sMEnvValueP = gMEnvKickP.next();

    int kickB = (int)sMEnvValueA * gMDOscKick.next();
    int kickA = (int)(kickB) >> 1;
    int kickSnd = (int)kickA >> 8;

    return kickSnd;

    // envelope.update();
    // return (int)(envelope.next() * kickSnd) >> 8;
}
