#ifndef PHASE_H_
#define PHASE_H_

#include <Oscil.h>
#include <Phasor.h>
#include <ReverbTank.h>
// #include <Sample.h>
#include "Envelope.h"
#include "Fix_Sample.h"

/*
random freq feature?

REVERB should be applied on top instead of being a type

might move the frequency picht out being part of sequencer
*/

#define PHASE_TYPE_COUNT 7
#define ENV_NUM_PHASE 3

enum { SIMPLE, REVERB, FREQ_ENV, PHASOR2, PHASOR3, SAMPLE, SAMPLE_FREQ };

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

    Envelope<CONTROL_RATE, ENV_NUM_PHASE> envlop{AUDIO_RATE};
    // Envelope<CONTROL_RATE, ENV_NUM_PHASE> envlopFreq{CONTROL_RATE};
    // // before to have PHASOR3 it was AUDIO_RATE
    Envelope<CONTROL_RATE, ENV_NUM_PHASE> envlopFreq{AUDIO_RATE};

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
        } else if (type == REVERB) {
            ptrUpdate =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::updateSimple;
            ptrNoteOn =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::noteOnSimple;
            ptrNext = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::nextReverb;
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
        } else if (type == SAMPLE) {
            ptrUpdate =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::updateNone;
            ptrNoteOn =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::noteOnSample;
            ptrNext = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::nextSample;
        } else if (type == SAMPLE_FREQ) {
            ptrUpdate = &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::updateFreq;
            ptrNoteOn =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::noteOnSampleFreq;
            ptrNext =
                &Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::nextSampleFreq;
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

    void setTable(const int8_t* table) {
        sample.setTable(table);
        oscil.setTable(table);
    }

   private:
    const float PDM_SCALE;
    int freqAdd;

    Oscil<NUM_TABLE_CELLS, AUDIO_RATE> oscil;
    Sample<NUM_TABLE_CELLS, AUDIO_RATE> sample;

    Phasor<AUDIO_RATE> phasor;
    Phasor<AUDIO_RATE> phasorFreq;

    ReverbTank reverb;

    byte previous_counter;

    int (Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::*ptrNext)();
    void (Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::*ptrUpdate)();
    void (Phase<NUM_TABLE_CELLS, PHASES_STEP_COUNT>::*ptrNoteOn)();

    void updateNone() {}

    void updateSimple() { envlop.update(); }

    void updateFreq() {
        updateSimple();
        envlopFreq.update();
    }

    void updatePhasor3() {
        updateFreq();
        float resonance_freq = frequency + freqAdd +
                               ((float)(frequency + freqAdd) *
                                ((float)envlopFreq.next() * PDM_SCALE));
        phasorFreq.setFreq(resonance_freq);
    }

    void noteOnSample() {
        sample.setFreq((float)(frequency + freqAdd));
        sample.start();
    }

    void noteOnSampleFreq() {
        noteOnSample();
        envlopFreq.play();
    }

    void noteOnSimple() {
        oscil.setFreq((int)(frequency + freqAdd));
        envlop.play();
    }

    void noteOnFreqEnv() {
        noteOnSimple();
        envlopFreq.play();
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
        return (envlop.next() *
                oscil.atIndex(phasorFreq.next() >> phasorShift)) >>
               1;
    }

    int nextPhasor3() {
        byte amp_ramp = 255 - handleCounter();
        return ((long)envlop.next() * amp_ramp *
                oscil.atIndex(phasorFreq.next() >> phasorShift)) >>
               8;
    }

    int nextReverb() {
        return (int)((reverb.next(envlop.next()) * oscil.next()) >> 1);
    }

    int nextSimple() { return (int)((envlop.next() * oscil.next()) >> 1); }

    int nextFreqEnv() {
        oscil.setFreq((int)frequency + freqAdd +
                      (envlopFreq.next() >> freqShift));
        return nextSimple();
    }

    int nextSample() { return (int)sample.next() << 8; }

    int nextSampleFreq() {
        sample.setFreq(
            (float)(frequency + freqAdd + (envlopFreq.next() >> freqShift)));
        return nextSample();
    }
};

#endif
