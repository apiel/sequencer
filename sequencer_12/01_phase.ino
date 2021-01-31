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

byte gSeqPhases[MAX_PATTERNS][STEP_COUNT] = {
    {D_KICK, 0, 0, 0, D_SNARE, 0, 0, 0, D_KICK, 0, 0, 0, D_SNARE, 0, 0, D_KICK},
    {D_KICK + D_CRASH, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT,
     0, D_CLAP, 0, D_HIHAT, D_KICK},
    {D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0},
    {D_PHASOR, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

byte gCurrentPattern[STEP_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0};

Phase<MAX_NUM_CELLS, STEP_COUNT> phases[MAX_PHASES];

void setupPhase(byte phase, byte tableId, byte type, int frequency) {
    const float adsrTimes[] = {0.0, 0.0, 0.0, 1.0};
    const byte adsrLevels[] = {200, 200, 200, 0};
    setupPhase(phase, tableId, type, frequency, adsrTimes, adsrLevels);
}

void setupPhase(byte phase, byte tableId, byte type, int frequency,
                const float adsrTimes[4], const byte adsrLevels[4]) {
    const float adsrFreqTimes[] = {0.0, 0.0, 0.0, 1.0};
    const byte adsrFreqLevels[] = {200, 200, 200, 0};
    setupPhase(phase, tableId, type, frequency, adsrTimes, adsrLevels,
               adsrFreqTimes, adsrFreqLevels);
}

void setupPhase(byte phase, byte tableId, byte type, int frequency,
                const float adsrTimes[4], const byte adsrLevels[4],
                const float adsrFreqTimes[4], const byte adsrFreqLevels[4]) {
    setTable(phase, tableId);

    lpf.setCutoffFreqAndResonance(gCutoff, gResonance);

    phases[phase].setType(type);
    phases[phase].frequency = frequency;

    phases[phase].adsr.setTimes(adsrTimes[0] * gTempo, adsrTimes[1] * gTempo,
                                adsrTimes[2] * gTempo, adsrTimes[3] * gTempo);
    phases[phase].adsr.setLevels(adsrLevels[0], adsrLevels[1], adsrLevels[2],
                                 adsrLevels[3]);

    phases[phase].adsrFreq.setTimes(
        adsrFreqTimes[0] * gTempo, adsrFreqTimes[1] * gTempo,
        adsrFreqTimes[2] * gTempo, adsrFreqTimes[3] * gTempo);
    phases[phase].adsrFreq.setLevels(adsrFreqLevels[0], adsrFreqLevels[1],
                                     adsrFreqLevels[2], adsrFreqLevels[3]);
}

#define MAX_PHASES_SETUP 2

void setupPhases(byte phasesSetupId) {
    gCurrentPhasesSetup = mod(phasesSetupId, MAX_PHASES_SETUP);

    if (gCurrentPhasesSetup == 0) {
        setupPhase(0, 20, FREQ_ENV, 45);
        // phases[0].freqSteps[0] = 100;
        // phases[0].freqSteps[4] = 400;
        // phases[0].freqSteps[8] = 200;
        // phases[0].freqSteps[12] = -300;

        // setupPhase(1, 20, PHASOR2, 150);
        setupPhase(1, 20, FREQ_ENV, 150);
        setupPhase(2, 10, SIMPLE, 2, (const float[4]){0.0, 0.0, 0.0, 0.3},
                   (const byte[4]){100, 100, 100, 0});
        setupPhase(3, 10, SIMPLE, 0);
        setupPhase(4, 10, SIMPLE, 0);
        setupPhase(5, 20, PHASOR3, 30, (const float[4]){1.0, 1.0, 12.0, 2.0},
                   (const byte[4]){70, 70, 70, 0},
                   (const float[4]){3.0, 5.0, 8.0, 2.0},
                   (const byte[4]){255, 100, 100, 0});
        phases[5].adsrFreq.setLerpRate(CONTROL_RATE);
    } else {
        setupPhase(0, 9, FREQ_ENV, 45);
        setupPhase(1, 20, PHASOR2, 150);
        setupPhase(2, 10, SIMPLE, 100);
        setupPhase(3, 4, SIMPLE, 0);
        setupPhase(4, 10, SIMPLE, 0);
        setupPhase(5, 18, PHASOR3, 30);
    }
}

void playPhase() {
    int aPhase = gCurrentPattern[gSeqStepIndex];

    for (int i = 0; i < MAX_PHASES; i++) {
        if (aPhase & (int)pow(2, i)) {
            phases[i].noteOn(gSeqStepIndex);
        }
    }
}

void updateEnvelopes() {
    for (int i = 0; i < MAX_PHASES; i++) {
        phases[i].update();
    }
}

int updateAudioSeq() {
    int ret = 0;
    for (int i = 0; i < MAX_PHASES; i++) {
        ret += phases[i].next();
    }

    // return ret >> 8;
    return lpf.next((int)(ret * gVolume / MAX_VOLUME)) >> 8;
    // return (int)(ret * gVolume /
    // MAX_VOLUME) >> 8;
}
