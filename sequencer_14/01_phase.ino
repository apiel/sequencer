/*
Make the frequency envlop table independent from the main envlop
So the frequency envlop doesnt have to be the same...

when pressing loop the pattern button become synth

Look at PDResonant it seem awesome :p
Look at synth in general:
- FMsynth
- WaveShaper?
*/

#include <LowPassFilter.h>

#include "Phase.h"

#define MAX_NUM_CELLS 8192

// seem to be kind of useless
LowPassFilter lpf;
byte gCutoff = 255;
byte gResonance = 0;

byte currentTableId = 0;

Phase<MAX_NUM_CELLS, STEP_COUNT> phases[MAX_PHASES];

void setupPhase(byte id, byte tableId, byte type, int frequency) {
    const float envlopTimes[] = {0.0, 0.0, 1.0};
    const byte envlopLevels[] = {200, 200, 0};
    setupPhase(id, tableId, type, frequency, envlopTimes, envlopLevels);
}

void setupPhase(byte id, byte tableId, byte type, int frequency,
                const float envlopTimes[3], const byte envlopLevels[3]) {
    const float envlopFreqTimes[] = {0.0, 0.0, 1.0};
    const byte envlopFreqLevels[] = {200, 200, 0};
    setupPhase(id, tableId, type, frequency, envlopTimes, envlopLevels,
               envlopFreqTimes, envlopFreqLevels);
}

void setupPhase(byte id, byte tableId, byte type, int frequency,
                const float envTimes[3], const byte envLevels[3],
                const float envFreqTimes[3], const byte envFreqLevels[3]) {
    setTable(id, tableId);

    lpf.setCutoffFreqAndResonance(gCutoff, gResonance);

    phases[id].setType(type);
    phases[id].frequency = frequency;

    phases[id].envlop.set(0, envTimes[0] * gTempo, envLevels[0]);
    phases[id].envlop.set(1, envTimes[1] * gTempo, envLevels[1]);
    phases[id].envlop.set(2, envTimes[2] * gTempo, envLevels[2]);

    phases[id].envlopFreq.set(0, envFreqTimes[0] * gTempo, envFreqLevels[0]);
    phases[id].envlopFreq.set(1, envFreqTimes[1] * gTempo, envFreqLevels[1]);
    phases[id].envlopFreq.set(2, envFreqTimes[2] * gTempo, envFreqLevels[2]);
}

#define MAX_PHASES_SETUP 2

void setupPhases(byte phasesSetupId) {
    gCurrentPhasesSetup = mod(phasesSetupId, MAX_PHASES_SETUP);

    if (gCurrentPhasesSetup == 0) {
        setupPhase(0, getTablesCount(), FREQ_ENV, 45);
        // phases[0].freqSteps[0] = 100;
        // phases[0].freqSteps[4] = 400;
        // phases[0].freqSteps[8] = 200;
        // phases[0].freqSteps[12] = -300;

        // setupPhase(1, 20, PHASOR2, 150);
        setupPhase(1, getTablesCount(), FREQ_ENV, 150);
        setupPhase(2, 10, SIMPLE, 2, (const float[3]){0.0, 0.0, 0.3},
                   (const byte[3]){100, 100, 0});
        setupPhase(3, 10, SIMPLE, 0);
        setupPhase(4, 10, SIMPLE, 0);
        setupPhase(5, getTablesCount(), PHASOR3, 30,
                   (const float[3]){1.0, 12.0, 2.0},
                   (const byte[3]){70, 70, 0},
                   (const float[3]){3.0, 8.0, 2.0},
                   (const byte[3]){255, 100, 0});
        phases[5].envlopFreq.setLerpRate(CONTROL_RATE);
    } else {
        setupPhase(0, 9, FREQ_ENV, 45);
        setupPhase(1, getTablesCount(), PHASOR2, 150);
        setupPhase(2, 10, SIMPLE, 100);
        setupPhase(3, 4, SIMPLE, 0);
        setupPhase(4, 10, SIMPLE, 0);
        setupPhase(5, 18, PHASOR3, 30);
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
