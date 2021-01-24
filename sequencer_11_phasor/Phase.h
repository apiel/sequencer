#ifndef PHASE_H_
#define PHASE_H_

#include <Oscil.h>
#include <Phasor.h>

#include "ADSR_FIX.h"

enum { SIMPLE, FREQ_ENV, PHASOR, PHASOR2 };

/*
Try to add setType function
with ptrFunction to update and next

Give a way to set a different table for adsrTable
*/

template <uint16_t NUM_TABLE_CELLS>
class Phase {
   public:
    byte type;
    const char* tableName;
    // here we could use an array to have a specific freq per step
    int freqAdd;
    unsigned int frequency;
    ADSR<CONTROL_RATE, AUDIO_RATE> adsr;
    ADSR<CONTROL_RATE, AUDIO_RATE> adsrFreq;
    byte freqShift;

    Phase() : PDM_SCALE(0.05) {
        freqAdd = 0;
        type = SIMPLE;
    }

    void noteOn() {
        if (type == FREQ_ENV) {
            noteOnFreqEnv();
        } else if (type >= PHASOR) {
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
        adsr.update();
        if (type != SIMPLE) {
            adsrFreq.update();
        }
    }

    int next() {
        if (type >= PHASOR) {
            if (type == PHASOR2) {
                byte counter = phasor.next() >> 24;
                if (counter < previous_counter) phasorFreq.set(0);
                previous_counter = counter;
            }
            return (adsr.next() * oscil.atIndex(phasorFreq.next() >> 21)) >> 1;
        }
        if (type == FREQ_ENV) {
            oscil.setFreq((int)frequency + (adsrFreq.next() >> freqShift));
        }
        return (int)((adsr.next() * oscil.next()) >> 1);
    }

    void setTable(const int8_t* TABLE_NAME) { oscil.setTable(TABLE_NAME); }

   private:
    const float PDM_SCALE;

    Oscil<NUM_TABLE_CELLS, AUDIO_RATE> oscil;
    Oscil<NUM_TABLE_CELLS, AUDIO_RATE> oscilFreq;

    Phasor<AUDIO_RATE> phasor;
    Phasor<AUDIO_RATE> phasorFreq;

    byte previous_counter;

    void noteOnSimple() {
        oscil.setFreq((int)(frequency + freqAdd));
        adsr.noteOn();
    }

    void noteOnFreqEnv() {
        noteOnSimple();
        adsrFreq.noteOn();
    }

    void noteOnPhasor() {
        noteOnFreqEnv();
        phasor.setFreq((int)(frequency + freqAdd));
        phasorFreq.setFreq((int)(frequency + freqAdd));
    }
};

#endif
