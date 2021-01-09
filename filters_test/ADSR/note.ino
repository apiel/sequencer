#include <tables/sin2048_int8.h>
#include <tables/triangle2048_int8.h>
#include <tables/whitenoise8192_int8.h>

// new

#include <tables/square_analogue512_int8.h>
#include <tables/cos256_int8.h>
#include <tables/noise_static_1_16384_int8.h>
#include <tables/phasor256_int8.h>

#include <ADSR.h>
#include <mozzi_rand.h>

ADSR<AUDIO_RATE, AUDIO_RATE> envelope;

unsigned int duration, attack, decay, sustain, release_ms;
byte sMEnvVal;
unsigned int sMReleaseTimeEnv = 250;
// new

#define DRUM_LEVEL 200

int sMFrequency = 45; // (setting)
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
// Oscil<SQUARE_ANALOGUE512_NUM_CELLS, AUDIO_RATE> gMDOscKickBis(SQUARE_ANALOGUE512_DATA);
// Oscil<COS256_NUM_CELLS, AUDIO_RATE> gMDOscKickBis(COS256_DATA); // not really diff
// Oscil<NOISE_STATIC_1_16384_NUM_CELLS, AUDIO_RATE> gMDOscKickBis(NOISE_STATIC_1_16384_DATA); // like a fuse
Oscil<PHASOR256_NUM_CELLS, AUDIO_RATE> gMDOscKickBis(PHASOR256_DATA);

// envelopes
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvKickA;
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvKickP;

byte count = 0;
void playNote()
{
    if (count < 100) {
        count++;
        byte aNote = gSeqNotes[gSeqNoteIndex];
        // 01 - kick
        if (aNote & D_KICK)
        {
            playDKick();
        }
    }
}

void playDKick()
{
    gMDOscKick.setFreq(sMFrequency);
    gMDOscKickBis.setFreq(sMFrequency);
    gMEnvKickA.noteOn();
    gMEnvKickP.noteOn();

    envelope.noteOn();
    envelope.noteOff();

    gMEnvKickA.noteOff();
    gMEnvKickP.noteOff();
}

void setupNotes()
{
    gMEnvKickA.setLevels(sMAttackLevel, sMDecayLevel, sMSustainLevel,
                         sMReleaseLevel);
    gMEnvKickA.setTimes(sMAttackTime, sMDecayTime, sMSustainTime,
                        sMReleaseTime);
    gMEnvKickP.setLevels(sMAttackLevel, sMDecayLevel, sMSustainLevel,
                         sMReleaseLevel);
    gMEnvKickP.setTimes(sMAttackTime, sMDecayTime, sMSustainTime,
                        sMReleaseTimeP);

    envelope.setLevels(sMAttackLevel, sMDecayLevel, sMSustainLevel,
                       sMReleaseLevel);
    envelope.setTimes(sMAttackTime, sMDecayTime, sMSustainTime,
                      sMReleaseTimeEnv);
}

void updateEnvelopes()
{
    gMEnvKickA.update();
    gMEnvKickP.update();
    envelope.update();

    int freq = sMFrequency 
        + (sMEnvValueP >> sMEnvSlope) 
        + (sMEnvVal >> 2);
    gMDOscKick.setFreq(freq);
    gMDOscKickBis.setFreq(freq);
    // Serial.print("freq: ");
    // Serial.println(freq);
}

int updateAudioSeq()
{
    sMEnvValueA = gMEnvKickA.next();
    sMEnvValueP = gMEnvKickP.next();
    sMEnvVal = envelope.next();

    // int kickB = (int)sMEnvValueA * gMDOscKick.next() + gMDOscKickBis.next();
    // int kickA = (int)(kickB) >> 1;
    // int kickSnd = (int)kickA >> 8;

    int kickA = (int)(sMEnvValueA * gMDOscKick.next()) >> 1;
    int kickB = (int)(sMEnvValueA * gMDOscKickBis.next()) >> 1;
    int kickSnd = (int)0
        // + kickA 
        + kickB 
            >> 8;

    return kickSnd;

    // envelope.update();
    // return (int)(envelope.next() * kickSnd) >> 8;
}
