#include "Phase.h"

#define MAX_NUM_CELLS 8192
#define STEP_COUNT 16

byte currentTableId = 0;

Phase<MAX_NUM_CELLS, STEP_COUNT> phase;

void setupPhase(byte tableId, byte type, int frequency) {
    const float adsrFreqTimes[] = {0.0, 0.0, 0.0, 1.0};
    const byte adsrFreqLevels[] = {200, 200, 200, 0};
    setupPhase(tableId, type, frequency, adsrFreqTimes, adsrFreqLevels);
}

void setupPhase(byte tableId, byte type, int frequency,
                const float adsrFreqTimes[4], const byte adsrFreqLevels[4]) {
    // const float adsrTimes[] = {0.1, 0.1, 0.7, 0.1};
    // const float adsrTimes[] = {0.5, 0.0, 0.0, 0.5};
    // const float adsrTimes[] = {0.0, 0.0, 0.0, 1.0};
    // const float adsrTimes[] = {1.0, 0.0, 0.0, 0.0};
    // const byte adsrLevels[] = {200, 150, 150, 0};
    // const byte adsrLevels[] = {200, 200, 200, 0};

    const float adsrTimes[] = {0.5, 0.5, 0.0, 0.0};
    const byte adsrLevels[] = {200, 1, 0, 0};

    setTable(tableId);

    phase.setType(type);
    phase.frequency = frequency;

    phase.adsr.setTimes(adsrTimes[0] * gTempo, adsrTimes[1] * gTempo,
                        adsrTimes[2] * gTempo, adsrTimes[3] * gTempo);
    phase.adsr.setLevels(adsrLevels[0], adsrLevels[1], adsrLevels[2],
                         adsrLevels[3]);

    phase.adsrFreq.setTimes(
        adsrFreqTimes[0] * gTempo, adsrFreqTimes[1] * gTempo,
        adsrFreqTimes[2] * gTempo, adsrFreqTimes[3] * gTempo);
    phase.adsrFreq.setLevels(adsrFreqLevels[0], adsrFreqLevels[1],
                             adsrFreqLevels[2], adsrFreqLevels[3]);
}

void setupPhases() {
    // setupPhase(getTablesCount(), FREQ_ENV, 45);
    setupPhase(9, SIMPLE, 45);


    // setupPhase(getTablesCount(), FREQ_ENV, 150);
    // setupPhase(10, SIMPLE, 2, (const float[4]){0.0, 0.0, 0.0, 0.3},
    //            (const byte[4]){100, 100, 100, 0});
    // setupPhase(10, SIMPLE, 0);
    // setupPhase(10, SIMPLE, 0);
    // setupPhase(
    //     getTablesCount(), PHASOR3, 30, (const float[4]){1.0, 1.0, 12.0, 2.0},
    //     (const byte[4]){70, 70, 70, 0}, (const float[4]){3.0, 5.0, 8.0, 2.0},
    //     (const byte[4]){255, 100, 100, 0});
    // phase.adsrFreq.setLerpRate(CONTROL_RATE);
}

void playPhase() { phase.noteOn(1); }

void updateEnvelopes() { phase.update(); }

int updateAudioSeq() { return (int)phase.next() >> 8; }
