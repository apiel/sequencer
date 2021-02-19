#include "Phase.h"

#define MAX_NUM_CELLS 8192
#define STEP_COUNT 16

byte currentTableId = 0;

Phase<MAX_NUM_CELLS, STEP_COUNT> phase;

void setupPhase(byte tableId, byte type, int frequency) {
    const float envlopFreqTimes[] = {0.0, 0.0, 1.0};
    const byte envlopFreqLevels[] = {200, 200, 0};
    setupPhase(tableId, type, frequency, envlopFreqTimes, envlopFreqLevels);
}

void setupPhase(byte tableId, byte type, int frequency,
                const float envlopFreqTimes[3],
                const byte envlopFreqLevels[3]) {
    // const float envlopTimes[] = {0.1, 0.1, 0.7, 0.1};
    // const float envlopTimes[] = {0.5, 0.0, 0.0, 0.5};
    // const float envlopTimes[] = {0.0, 0.0, 0.0, 1.0};
    // const float envlopTimes[] = {1.0, 0.0, 0.0, 0.0};
    // const byte envlopLevels[] = {200, 150, 150, 0};
    // const byte envlopLevels[] = {200, 200, 200, 0};

    // const float envlopTimes[] = {0.5, 0.5, 0.0};
    // const byte envlopLevels[] = {200, 1, 0};

    // ToDo make min level value to 1
    const float envlopTimes[] = {0.3, 0.5, 0.2};
    const byte envlopLevels[] = {150, 150, 1};

    setTable(tableId);

    phase.setType(type);
    phase.frequency = frequency;

    phase.envlop.set(0, envlopTimes[0] * gTempo, envlopLevels[0]);
    phase.envlop.set(1, envlopTimes[1] * gTempo, envlopLevels[1]);
    phase.envlop.set(2, envlopTimes[2] * gTempo, envlopLevels[2]);

    phase.envlopFreq.set(0, envlopFreqTimes[0] * gTempo, envlopFreqLevels[0]);
    phase.envlopFreq.set(1, envlopFreqTimes[1] * gTempo, envlopFreqLevels[1]);
    phase.envlopFreq.set(2, envlopFreqTimes[2] * gTempo, envlopFreqLevels[2]);
}

void setupPhases() {
    // setupPhase(getTablesCount(), FREQ_ENV, 45);
    setupPhase(9, SIMPLE, 45);
    // setupPhase(9, SIMPLE, 45,(const float[3]){0.0, 0.0, 0.3},
    //            (const byte[3]){100, 100, 0});

    // setupPhase(getTablesCount(), FREQ_ENV, 150);
    // setupPhase(10, SIMPLE, 2, (const float[4]){0.0, 0.0, 0.0, 0.3},
    //            (const byte[4]){100, 100, 100, 0});
    // setupPhase(10, SIMPLE, 0);
    // setupPhase(10, SIMPLE, 0);
    // setupPhase(
    //     getTablesCount(), PHASOR3, 30, (const float[4]){1.0, 1.0, 12.0, 2.0},
    //     (const byte[4]){70, 70, 70, 0}, (const float[4]){3.0, 5.0, 8.0, 2.0},
    //     (const byte[4]){255, 100, 100, 0});
    // phase.envlopFreq.setLerpRate(CONTROL_RATE);
}

void playPhase() { phase.noteOn(1); }
void updateEnvelopes() { phase.update(); }
int updateAudioSeq() { return (int)phase.next() >> 8; }
