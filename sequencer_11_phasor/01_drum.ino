/*
Make the frequency adsr table independent from the main adsr
So the frequency adsr doesnt have to be the same...

when pressing loop the pattern button become synth

Look at PDResonant it seem awesome :p
Look at synth in general:
- FMsynth
- WaveShaper?
*/

#include <LowPassFilter.h>

#include "Phase.h"

#define D_KICK 1
#define D_SNARE 2
#define D_HIHAT 4
#define D_CLAP 8
#define D_CRASH 16
#define D_TOMHI 32

#define MAX_NUM_CELLS 8192

// seem to be kind of useless
LowPassFilter lpf;
byte gCutoff = 255;
byte gResonance = 0;

byte currentTableId = 0;

byte gSeqDrums[MAX_PATTERNS][MAX_DRUMS] = {
    {D_KICK, 0, D_HIHAT, 0, D_SNARE, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0,
     D_SNARE, 0, D_HIHAT, D_KICK},
    {D_KICK + D_CRASH, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT,
     0, D_CLAP, 0, D_HIHAT, D_KICK},
    {D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0}};

byte gCurrentPattern[MAX_DRUMS] = {0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0};

byte gCurrentPatternId = 0;

Phase<MAX_NUM_CELLS> phases[DRUMS_COUNT];

void setupDrum(byte drum, byte tableId, byte type, int frequency) {
    setTable(drum, tableId);

    lpf.setCutoffFreqAndResonance(gCutoff, gResonance);

    phases[drum].setType(type);
    phases[drum].frequency = frequency;

    phases[drum].adsr.setTimes(0, 0, 0, gTempo);
    phases[drum].adsr.setLevels(250, 200, 200, 0);

    phases[drum].adsrFreq.setTimes(0, 0, 0, gTempo);
    phases[drum].adsrFreq.setLevels(200, 200, 200, 0);
    phases[drum].freqShift = 1;
}

void setupDrums() {
    assignCurrentPattern(gCurrentPatternId);

    setupDrum(0, 20, FREQ_ENV, 45);
    setupDrum(1, 20, PHASOR2, 150);
    setupDrum(2, 10, SIMPLE, 100);
    setupDrum(3, 10, SIMPLE, 0);
    setupDrum(4, 10, SIMPLE, 0);
    setupDrum(5, 2, SIMPLE, 100);
}

void updateEnvelopes() {
    for (int i = 0; i < DRUMS_COUNT; i++) {
        phases[i].update();
    }
}

int updateAudioSeq() {
    int ret = 0;
    for (int i = 0; i < DRUMS_COUNT; i++) {
        ret += phases[i].next();
    }

    // return ret >> 8;
    return lpf.next((int)(ret * gVolume / MAX_VOLUME)) >> 8;
    // return (int)(ret * gVolume / MAX_VOLUME) >> 8;
}
