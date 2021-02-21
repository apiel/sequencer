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

#include "Tone.h"

#define MAX_NUM_CELLS 8192

// seem to be kind of useless
LowPassFilter lpf;
byte gCutoff = 255;
byte gResonance = 0;

byte currentTableId = 0;

Tone<MAX_NUM_CELLS, STEP_COUNT> tones[MAX_TONES];

void setupTone(byte id, byte tableId, byte type, int frequency) {
    const float envlopTimes[] = {0.0, 0.0, 1.0};
    const byte envlopLevels[] = {200, 200, 0};
    setupTone(id, tableId, type, frequency, envlopTimes, envlopLevels);
}

void setupTone(byte id, byte tableId, byte type, int frequency,
                const float envlopTimes[3], const byte envlopLevels[3]) {
    const float envlopFreqTimes[] = {0.0, 0.0, 1.0};
    const byte envlopFreqLevels[] = {200, 200, 0};
    setupTone(id, tableId, type, frequency, envlopTimes, envlopLevels,
               envlopFreqTimes, envlopFreqLevels);
}

void setupTone(byte id, byte tableId, byte type, int frequency,
                const float envTimes[3], const byte envLevels[3],
                const float envFreqTimes[3], const byte envFreqLevels[3]) {
    setTable(id, tableId);

    lpf.setCutoffFreqAndResonance(gCutoff, gResonance);

    tones[id].setType(type);
    tones[id].frequency = frequency;

    tones[id].envlop.set(0, envTimes[0] * gTempo, envLevels[0]);
    tones[id].envlop.set(1, envTimes[1] * gTempo, envLevels[1]);
    tones[id].envlop.set(2, envTimes[2] * gTempo, envLevels[2]);

    tones[id].envlopFreq.set(0, envFreqTimes[0] * gTempo, envFreqLevels[0]);
    tones[id].envlopFreq.set(1, envFreqTimes[1] * gTempo, envFreqLevels[1]);
    tones[id].envlopFreq.set(2, envFreqTimes[2] * gTempo, envFreqLevels[2]);
}

#define MAX_TONES_SETUP 2

void setupTones(byte tonesSetupId) {
    gCurrentTonesSetup = mod(tonesSetupId, MAX_TONES_SETUP);

    if (gCurrentTonesSetup == 0) {
        setupTone(0, getTablesCount(), FREQ_ENV, 45);
        // tones[0].freqSteps[0] = 100;
        // tones[0].freqSteps[4] = 400;
        // tones[0].freqSteps[8] = 200;
        // tones[0].freqSteps[12] = -300;

        // setupTone(1, 20, PHASOR2, 150);
        setupTone(1, getTablesCount(), FREQ_ENV, 150);
        setupTone(2, 10, SIMPLE, 2, (const float[3]){0.0, 0.0, 0.3},
                   (const byte[3]){100, 100, 0});
        setupTone(3, 10, SIMPLE, 0);
        setupTone(4, 10, SIMPLE, 0);
        setupTone(5, getTablesCount(), PHASOR3, 30,
                   (const float[3]){1.0, 12.0, 2.0},
                   (const byte[3]){70, 70, 0},
                   (const float[3]){3.0, 8.0, 2.0},
                   (const byte[3]){255, 100, 0});
        tones[5].envlopFreq.setLerpRate(CONTROL_RATE);
    } else {
        setupTone(0, 9, FREQ_ENV, 45);
        setupTone(1, getTablesCount(), PHASOR2, 150);
        setupTone(2, 10, SIMPLE, 100);
        setupTone(3, 4, SIMPLE, 0);
        setupTone(4, 10, SIMPLE, 0);
        setupTone(5, 18, PHASOR3, 30);
    }
}

void updateEnvelopes() {
    for (int i = 0; i < MAX_TONES; i++) {
        tones[i].update();
    }
}

int updateAudioSeq() {
    int ret = 0;
    for (int i = 0; i < MAX_TONES; i++) {
        ret += tones[i].next();
    }

    // return ret >> 8;
    return lpf.next((int)(ret * gVolume / MAX_VOLUME)) >> 8;
    // return (int)(ret * gVolume /
    // MAX_VOLUME) >> 8;
}
