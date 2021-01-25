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
#define D_PHASOR 32

#define MAX_NUM_CELLS 8192

// seem to be kind of useless
LowPassFilter lpf;
byte gCutoff = 255;
byte gResonance = 0;

byte currentTableId = 0;

byte gSeqPhases[MAX_PATTERNS][MAX_PHASES] = {
    {D_KICK, 0, D_HIHAT, 0, D_SNARE, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0,
     D_SNARE, 0, D_HIHAT, D_KICK},
    {D_KICK + D_CRASH, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT,
     0, D_CLAP, 0, D_HIHAT, D_KICK},
    {D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0},
    {D_PHASOR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

byte gCurrentPattern[MAX_PHASES] = {0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0};

byte gCurrentPatternId = 0;

Phase<MAX_NUM_CELLS> phases[PHASES_COUNT];

void setupPhase(byte phase, byte tableId, byte type, int frequency) {
    setTable(phase, tableId);

    lpf.setCutoffFreqAndResonance(gCutoff, gResonance);

    phases[phase].setType(type);
    phases[phase].frequency = frequency;

    phases[phase].adsr.setTimes(0, 0, 0, gTempo);
    phases[phase].adsr.setLevels(250, 200, 200, 0);

    phases[phase].adsrFreq.setTimes(0, 0, 0, gTempo);
    phases[phase].adsrFreq.setLevels(200, 200, 200, 0);
}

void setupPhases() {
    assignCurrentPattern(gCurrentPatternId);

    setupPhase(0, 20, FREQ_ENV, 45);
    // setupPhase(1, 20, PHASOR2, 150);
    setupPhase(1, 20, FREQ_ENV, 150);
    setupPhase(2, 10, SIMPLE, 100);
    setupPhase(3, 10, SIMPLE, 0);
    setupPhase(4, 10, SIMPLE, 0);

    setupPhase(5, 20, PHASOR3, 30);
    phases[5].adsr.setADLevels(255, 255);
    phases[5].adsr.setTimes(gTempo, gTempo, gTempo * 8, gTempo * 2);
    phases[5].adsrFreq.setADLevels(255, 100);
    phases[5].adsrFreq.setTimes(gTempo * 3, gTempo * 5, gTempo * 8, gTempo * 2);
}

void updateEnvelopes() {
    for (int i = 0; i < PHASES_COUNT; i++) {
        phases[i].update();
    }
}

int updateAudioSeq() {
    int ret = 0;
    for (int i = 0; i < PHASES_COUNT; i++) {
        ret += phases[i].next();
    }
    
    // return ret >> 8;
    return lpf.next((int)(ret * gVolume / MAX_VOLUME)) >> 8;
    // return (int)(ret * gVolume / MAX_VOLUME) >> 8;
}
