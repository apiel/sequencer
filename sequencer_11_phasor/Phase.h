#ifndef PHASE_H_
#define PHASE_H_

#include <Oscil.h>
#include <Phasor.h>

#include "ADSR_FIX.h"

/*
random freq feature

see if we can modulate the speed of phasor
*/

enum { SIMPLE, FREQ_ENV, PHASOR, PHASOR2, PHASOR3 };

template <uint16_t NUM_TABLE_CELLS, byte PHASES_STEP_COUNT>
class Phase {
   public:
    byte type;
    const char* tableName;
    int freqSteps[PHASES_STEP_COUNT] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    unsigned int frequency;
    byte freqShift;
    byte phasorShift;

    ADSR<CONTROL_RATE, AUDIO_RATE> adsr;
    ADSR<CONTROL_RATE, CONTROL_RATE> adsrFreq;
    // // before to have PHASOR3 it was AUDIO_RATE
    // ADSR<CONTROL_RATE, AUDIO_RATE> adsrFreq;

    Phase() : PDM_SCALE(0.05) {
        freqAdd = 0;
        freqShift = 1;
        phasorShift = 21;
        setType(SIMPLE);
    }

    void setType(byte newType) {
        type = newType;
        if (type == FREQ_ENV) {
            ptrUpdate = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::updateFreq;
            ptrNoteOn =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::noteOnFreqEnv;
            ptrNext = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::nextFreqEnv;
        } else if (type == PHASOR) {
            ptrUpdate = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::updateFreq;
            ptrNoteOn =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::noteOnPhasor;
            ptrNext = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::nextPhasor;
        } else if (type == PHASOR2) {
            ptrUpdate = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::updateFreq;
            ptrNoteOn =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::noteOnPhasor;
            ptrNext = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::nextPhasor2;
        } else if (type == PHASOR3) {
            ptrUpdate =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::updatePhasor3;
            ptrNoteOn =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::noteOnPhasor;
            ptrNext = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::nextPhasor3;
        } else {
            ptrUpdate =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::updateSimple;
            ptrNoteOn =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::noteOnSimple;
            ptrNext = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::nextSimple;
        }
    }

    void noteOn(byte step) {
        freqAdd = freqSteps[step];
        (this->*ptrNoteOn)();
    }

    void noteOn() {
        freqAdd = 0;
        (this->*ptrNoteOn)();
    }

    void update() { (this->*ptrUpdate)(); }

    int next() { return (this->*ptrNext)(); }

    void setTable(const int8_t* table) { oscil.setTable(table); }

   private:
    const float PDM_SCALE;
    int freqAdd;

    Oscil<NUM_TABLE_CELLS, AUDIO_RATE> oscil;

    Phasor<AUDIO_RATE> phasor;
    Phasor<AUDIO_RATE> phasorFreq;

    byte previous_counter;

    int (Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::*ptrNext)();
    void (Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::*ptrUpdate)();
    void (Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::*ptrNoteOn)();

    void updateSimple() { adsr.update(); }

    void updateFreq() {
        updateSimple();
        adsrFreq.update();
    }

    void updatePhasor3() {
        updateFreq();
        float resonance_freq = frequency + freqAdd +
                               ((float)(frequency + freqAdd) *
                                ((float)adsrFreq.next() * PDM_SCALE));
        phasorFreq.setFreq(resonance_freq);
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
        noteOnFreqEnv();
        phasor.setFreq((int)(frequency + freqAdd));
        phasorFreq.setFreq((int)(frequency + freqAdd));
    }

    int nextPhasor() {
        return (adsr.next() *
                oscil.atIndex(phasorFreq.next() >> phasorShift)) >>
               1;
    }

    byte handleCounter() {
        byte counter = phasor.next() >> 24;
        if (counter < previous_counter) phasorFreq.set(0);
        previous_counter = counter;

        return counter;
    }

    int nextPhasor2() {
        handleCounter();
        return nextPhasor();
    }

    int nextPhasor3() {
        byte amp_ramp = 255 - handleCounter();
        return ((long)adsr.next() * amp_ramp *
                oscil.atIndex(phasorFreq.next() >> phasorShift)) >>
               8;
    }

    int nextSimple() { return (int)((adsr.next() * oscil.next()) >> 1); }

    int nextFreqEnv() {
        oscil.setFreq((int)frequency + freqAdd +
                      (adsrFreq.next() >> freqShift));
        return nextSimple();
    }
};

#endif
