#ifndef PHASE_H_
#define PHASE_H_

#include <Oscil.h>
#include <Phasor.h>

#include "ADSR_FIX.h"

/*
random freq feature

maybe we should have FREQ_ENV2 with ADSR<CONTROL_RATE, AUDIO_RATE> adsrFreq;
or see if we can use different audio rate
*/

#define PHASE_TYPE_COUNT 4

enum { SIMPLE, FREQ_ENV, PHASOR2, PHASOR3 };

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
    ADSR<CONTROL_RATE, AUDIO_RATE> adsrFreq0;
    ADSR<CONTROL_RATE, CONTROL_RATE> adsrFreq1;

    Phase() : PDM_SCALE(0.05) {
        freqAdd = 0;
        freqShift = 1;
        phasorShift = 21;
        setType(SIMPLE);
        setAdsrFreqType(0);
    }

    void setAdsrFreqType(byte idx) {
        if (idx == 0) {
            ptrAdsrFreqNext =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::adsrFreq0Next;
            ptrAdsrFreqUpdate =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::adsrFreq0Update;
            ptrAdsrFreqNoteOn =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::adsrFreq0NoteOn;
        } else {
            ptrAdsrFreqNext =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::adsrFreq1Next;
            ptrAdsrFreqUpdate =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::adsrFreq1Update;
            ptrAdsrFreqNoteOn =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::adsrFreq1NoteOn;
        }
    }

    void setType(byte newType) {
        type = newType;
        if (type == FREQ_ENV) {
            ptrUpdate = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::updateFreq;
            ptrNoteOn =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::noteOnFreqEnv;
            ptrNext = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::nextFreqEnv;
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

    int (Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::*ptrAdsrFreqNext)();
    void (Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::*ptrAdsrFreqUpdate)();
    void (Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::*ptrAdsrFreqNoteOn)();

    int adsrFreq0Next { return adsrFreq0.next(); }
    void adsrFreq0Update { adsrFreq0.update(); }
    void adsrFreq0NoteOn { adsrFreq0.nodeOn(); }
    int adsrFreq1Next { return adsrFreq1.next(); }
    void adsrFreq1Update { adsrFreq1.update(); }
    void adsrFreq1NoteOn { adsrFreq1.nodeOn(); }

    void updateSimple() { adsr.update(); }

    void updateFreq() {
        updateSimple();
        ptrAdsrFreqUpdate();
    }

    void updatePhasor3() {
        updateFreq();
        float resonance_freq = frequency + freqAdd +
                               ((float)(frequency + freqAdd) *
                                ((float)ptrAdsrFreqNext() * PDM_SCALE));
        phasorFreq.setFreq(resonance_freq);
    }

    void noteOnSimple() {
        oscil.setFreq((int)(frequency + freqAdd));
        adsr.noteOn();
    }

    void noteOnFreqEnv() {
        noteOnSimple();
        ptrAdsrFreqNoteOn();
    }

    void noteOnPhasor() {
        noteOnFreqEnv();
        phasor.setFreq((int)(frequency + freqAdd));
        phasorFreq.setFreq((int)(frequency + freqAdd));
    }

    byte handleCounter() {
        byte counter = phasor.next() >> 24;
        if (counter < previous_counter) phasorFreq.set(0);
        previous_counter = counter;

        return counter;
    }

    int nextPhasor2() {
        handleCounter();
        return (adsr.next() *
                oscil.atIndex(phasorFreq.next() >> phasorShift)) >>
               1;
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
                      (ptrAdsrFreqNext() >> freqShift));
        return nextSimple();
    }
};

#endif
