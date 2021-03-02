#ifndef TONE_H_
#define TONE_H_

#include "ToneBase.h"

#define NUM_TABLE_CELLS 8192

#define FREQ_ENV_PHASES 6

// need to add feature to play as a synth from synth 01


class Tone : public ToneBase<NUM_TABLE_CELLS, 3, FREQ_ENV_PHASES> {
   public:
    bool isDrum = true;
    byte id = 0;

    byte distribute = 0;
    byte timePct[FREQ_ENV_PHASES] = {
        100 / FREQ_ENV_PHASES, 100 / FREQ_ENV_PHASES, 100 / FREQ_ENV_PHASES,
        100 / FREQ_ENV_PHASES, 100 / FREQ_ENV_PHASES, 100 / FREQ_ENV_PHASES};

    void updateFreqTimes() {
        unsigned int ms = envlop.getTotalTime();
        for (byte i = 0; i < FREQ_ENV_PHASES; i++) {
            setEnvlopFreq(i, ms * timePct[i] / 100,
                          envlopFreq.getLevel(i) - FREQ_ENV_BASE);
        }
        balancePct(255);
    }

    void setEnvlop(byte index, unsigned int msec, int value) {
        envlop.set(index, msec, value);
        updateFreqTimes();
    }

    void incFreqTime(byte index, int value) {
        timePct[index] = between(timePct[index] + value, 0, 100);
        balancePct(index);
        updateFreqTimes();
    }

   protected:
    int between(int val, int minVal, int maxVal) {
        return min(max(val, minVal), maxVal);
    }

    void balancePct(byte index) {
        while (sumPct() != 100) {
            distribute = (distribute + 1) % FREQ_ENV_PHASES;
            if (distribute != index) {
                timePct[distribute] = between(
                    timePct[distribute] - (sumPct() > 100 ? 1 : -1), 0, 100);
            }
        }
    }

    byte sumPct() {
        byte pct = 0;
        for (byte i = 0; i < FREQ_ENV_PHASES; i++) {
            pct += timePct[i];
        }
        return pct;
    }
};

#endif
