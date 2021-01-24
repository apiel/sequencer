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
        setType(SIMPLE);
    }

    void setType(byte newType) {
        type = newType;
        if (type == FREQ_ENV) {
            ptrUpdate = &Phase<NUM_TABLE_CELLS>::updateFreq;
            ptrNoteOn = &Phase<NUM_TABLE_CELLS>::noteOnFreqEnv;
            ptrNext = &Phase<NUM_TABLE_CELLS>::nextFreqEnv;
        } else if (type == PHASOR) {
            ptrUpdate = &Phase<NUM_TABLE_CELLS>::updateFreq;
            ptrNoteOn = &Phase<NUM_TABLE_CELLS>::noteOnPhasor;
            ptrNext = &Phase<NUM_TABLE_CELLS>::nextPhasor;
        } else if (type == PHASOR2) {
            ptrUpdate = &Phase<NUM_TABLE_CELLS>::updateFreq;
            ptrNoteOn = &Phase<NUM_TABLE_CELLS>::noteOnPhasor;
            ptrNext = &Phase<NUM_TABLE_CELLS>::nextPhasor2;
        } else {
            ptrUpdate = &Phase<NUM_TABLE_CELLS>::updateSimple;
            ptrNoteOn = &Phase<NUM_TABLE_CELLS>::noteOnSimple;
            ptrNext = &Phase<NUM_TABLE_CELLS>::nextSimple;
        }
    }

    void noteOn(int add) {
        freqAdd = add;
        noteOn();
    }

    void noteOn() { (this->*ptrNoteOn)(); }

    void update() { (this->*ptrUpdate)(); }
    
    int next() { return (this->*ptrNext)(); }

    void setTable(const int8_t* TABLE_NAME) { oscil.setTable(TABLE_NAME); }

   private:
    const float PDM_SCALE;

    Oscil<NUM_TABLE_CELLS, AUDIO_RATE> oscil;
    Oscil<NUM_TABLE_CELLS, AUDIO_RATE> oscilFreq;

    Phasor<AUDIO_RATE> phasor;
    Phasor<AUDIO_RATE> phasorFreq;

    byte previous_counter;

    int (Phase<NUM_TABLE_CELLS>::*ptrNext)();
    void (Phase<NUM_TABLE_CELLS>::*ptrUpdate)();
    void (Phase<NUM_TABLE_CELLS>::*ptrNoteOn)();

    void updateSimple() { adsr.update(); }

    void updateFreq() {
        updateSimple();
        adsrFreq.update();
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
        return (adsr.next() * oscil.atIndex(phasorFreq.next() >> 21)) >> 1;
    }

    int nextPhasor2() {
        byte counter = phasor.next() >> 24;
        if (counter < previous_counter) phasorFreq.set(0);
        previous_counter = counter;

        return nextPhasor();
    }

    int nextSimple() { return (int)((adsr.next() * oscil.next()) >> 1); }

    int nextFreqEnv() {
        oscil.setFreq((int)frequency + (adsrFreq.next() >> freqShift));
        return nextSimple();
    }
};

#endif
