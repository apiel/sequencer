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

#define MAX_TONES 6  // number of existing tones

#define TONE_A 0
#define TONE_B 1
#define TONE_C 2
#define TONE_D 3
#define TONE_E 4
#define TONE_F 5

// seem to be kind of useless
LowPassFilter lpf;
byte gCutoff = 255;
byte gResonance = 0;

byte currentTableId = 0;

Tone<MAX_NUM_CELLS> tones[MAX_TONES];

void setupTone(byte id, byte tableId, byte type, int frequency) {
    setupTone(id, tableId, type, frequency, (const float[2]){0.0, 1.0},
              (const byte[2]){200, 0});
}

void setupTone(byte id, byte tableId, byte type, int frequency,
               const float envlopTimes[2], const byte envlopLevels[2]) {
    setupTone(id, tableId, type, frequency, envlopTimes, envlopLevels,
              (const float[3]){0.0, 0.0, 1.0}, (const byte[3]){200, 200, 0});
}

void setupTone(byte id, byte tableId, byte type, int frequency,
               const float envTimes[2], const byte envLevels[2],
               const float envFreqTimes[3], const byte envFreqLevels[3]) {
    setTable(id, tableId);

    lpf.setCutoffFreqAndResonance(gCutoff, gResonance);

    tones[id].setType(type);
    tones[id].frequency = frequency;

    tones[id].envlop.set(0, envTimes[0] * gTempo, envLevels[0]);
    tones[id].envlop.set(1, envTimes[1] * gTempo, envLevels[1]);

    tones[id].envlopFreq.set(0, envFreqTimes[0] * gTempo, envFreqLevels[0]);
    tones[id].envlopFreq.set(1, envFreqTimes[1] * gTempo, envFreqLevels[1]);
    tones[id].envlopFreq.set(2, envFreqTimes[2] * gTempo, envFreqLevels[2]);
}

#define MAX_TONES_SETUP 2

void setupTones(byte tonesSetupId) {
    gCurrentTonesSetup = mod(tonesSetupId, MAX_TONES_SETUP);

    if (gCurrentTonesSetup == 0) {
        setupTone(TONE_A, getTablesCount(), SIMPLE, 45);
        // tones[0].freqSteps[0] = 100;
        // tones[0].freqSteps[4] = 400;
        // tones[0].freqSteps[8] = 200;
        // tones[0].freqSteps[12] = -300;

        setupTone(TONE_B, getTablesCount(), SIMPLE, 150);
        tones[TONE_B].substain = false;

        // setupTone(TONE_B, getTablesCount(), SIMPLE, 150, (const
        // float[2]){0.0, 0.8},
        //           (const byte[2]){100, 0});
        // setupTone(TONE_B, getTablesCount(), SIMPLE, 150, (const
        // float[3]){0.0, 7.3, 0.7},
        //           (const byte[3]){100, 100, 1});

        setupTone(TONE_C, 10, SIMPLE, 2, (const float[2]){0.0, 0.3},
                  (const byte[2]){100, 1});
        tones[TONE_C].substain = false;

        setupTone(TONE_D, 10, SIMPLE, 0);
        setupTone(TONE_E, 10, SIMPLE, 0);
        setupTone(TONE_F, getTablesCount(), PHASOR3, 30,
                  (const float[2]){1.0, 2.0}, (const byte[2]){70, 1},
                  (const float[3]){3.0, 8.0, 2.0},
                  (const byte[3]){255, 100, 0});
        tones[5].envlopFreq.setLerpRate(CONTROL_RATE);
    } else {
        setupTone(TONE_A, 9, SIMPLE, 45);
        setupTone(TONE_B, getTablesCount(), PHASOR2, 150);
        setupTone(TONE_C, 10, SIMPLE, 100);
        setupTone(TONE_D, 4, SIMPLE, 0);
        setupTone(TONE_E, 10, SIMPLE, 0);
        setupTone(TONE_F, 18, PHASOR3, 30);
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
