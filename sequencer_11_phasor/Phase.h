#ifndef PHASE_H_
#define PHASE_H_

#include <Phasor.h>

#include "ADSR_FIX.h"

enum { SIMPLE, FREQ_ENV, PHASOR };

template <uint16_t NUM_TABLE_CELLS>
class Phase {
   public:
    byte type;
    const char* name;
    int freqAdd;
    unsigned int frequency;
    ADSR<CONTROL_RATE, AUDIO_RATE> adsr;
    ADSR<CONTROL_RATE, AUDIO_RATE> adsrFreq;
    byte freqShift;

    Phase() : PDM_SCALE(0.05) { freqAdd = 0; }

    void noteOn() {
        if (type == FREQ_ENV) {
            noteOnFreqEnv();
        } else if (type == PHASOR) {
            noteOnPhasor();
        } else {
            noteOnSimple();
        }
    }

    void noteOn(int add) {
        freqAdd = add;
        noteOn();
    }

    void update() {
        if (type != SIMPLE) {
            adsrFreq.update();
        }
        adsr.update();

        if (type == PHASOR) {
            phasorFreq.setFreq(
                frequency + freqAdd +
                ((frequency + freqAdd) * adsrFreq.next() * PDM_SCALE));
        }
    }

    int next() {
        if (type == PHASOR) {
            return nextPhasor();
        }
        if (type == FREQ_ENV) {
            int freq = frequency + (adsrFreq.next() >> freqShift);
            oscil.setFreq(freq);
        }
        return (int)((adsr.next() * oscil.next()) >> 1);
    }

   private:
    const float PDM_SCALE;

    Oscil<NUM_TABLE_CELLS, AUDIO_RATE> oscil;
    Oscil<NUM_TABLE_CELLS, AUDIO_RATE> oscilFreq;

    Phasor<AUDIO_RATE> phasor;
    Phasor<AUDIO_RATE> phasorFreq;

    int nextPhasor() {
        static byte previous_counter;
        byte counter = phasor.next() >> 24;

        if (counter < previous_counter) phasorFreq.set(0);
        previous_counter = counter;

        unsigned int index = phasorFreq.next() >> 21;  // >>10 is really cool

        return (adsr.next() * (255 - counter) * oscil.atIndex(index)) >> 16;
    }

    void noteOnSimple() {
        oscil.setFreq((int)(frequency + freqAdd));
        adsr.noteOn();
    }

    void noteOnFreqEnv() {
        noteOnSimple();
        adsrFreq.noteOn();
    }

    void noteOnPhasor() {
        adsr.noteOn();
        adsrFreq.noteOn();
        phasor.setFreq((int)(frequency + freqAdd));
        phasorFreq.setFreq((int)(frequency + freqAdd));
    }
};

#endif
