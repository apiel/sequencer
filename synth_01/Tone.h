#ifndef TONE_H_
#define TONE_H_

#include <Oscil.h>
#include <Phasor.h>
#include <ReverbTank.h>
// #include <Sample.h>
#include "Envelope.h"
#include "Fix_Sample.h"

/*
REVERB should be applied on top instead of being a type
--> add after int next() { return (this->*ptrNext)(); }

having separate type for FREQ env might not be necessary
*/

#define TONE_TYPE_COUNT 7
#define ENV_NUM_PHASE 3

enum { SIMPLE, REVERB, FREQ_ENV, PHASOR2, PHASOR3, SAMPLE, SAMPLE_FREQ };

template <uint16_t NUM_TABLE_CELLS>
class Tone {
   public:
    byte type;
    const char* tableName;
    unsigned int frequency;
    byte freqShift;
    byte phasorShift;

    Envelope<CONTROL_RATE, ENV_NUM_PHASE> envlop{AUDIO_RATE};
    // Envelope<CONTROL_RATE, ENV_NUM_PHASE> envlopFreq{CONTROL_RATE};
    // // before to have PHASOR3 it was AUDIO_RATE
    Envelope<CONTROL_RATE, ENV_NUM_PHASE> envlopFreq{AUDIO_RATE};

    Tone() : PDM_SCALE(0.05) {
        freqAdd = 0;
        freqShift = 1;
        phasorShift = 21;
        setType(SIMPLE);
    }

    void setType(byte newType) {
        type = newType;
        if (type == FREQ_ENV) {
            ptrUpdate = &Tone<NUM_TABLE_CELLS>::updateFreq;
            ptrNoteOn =
                &Tone<NUM_TABLE_CELLS>::noteOnFreqEnv;
            ptrNext = &Tone<NUM_TABLE_CELLS>::nextFreqEnv;
        } else if (type == REVERB) {
            ptrUpdate =
                &Tone<NUM_TABLE_CELLS>::updateSimple;
            ptrNoteOn =
                &Tone<NUM_TABLE_CELLS>::noteOnSimple;
            ptrNext = &Tone<NUM_TABLE_CELLS>::nextReverb;
        } else if (type == PHASOR2) {
            ptrUpdate = &Tone<NUM_TABLE_CELLS>::updateFreq;
            ptrNoteOn =
                &Tone<NUM_TABLE_CELLS>::noteOnPhasor;
            ptrNext = &Tone<NUM_TABLE_CELLS>::nextPhasor2;
        } else if (type == PHASOR3) {
            ptrUpdate =
                &Tone<NUM_TABLE_CELLS>::updatePhasor3;
            ptrNoteOn =
                &Tone<NUM_TABLE_CELLS>::noteOnPhasor;
            ptrNext = &Tone<NUM_TABLE_CELLS>::nextPhasor3;
        } else if (type == SAMPLE) {
            ptrUpdate =
                &Tone<NUM_TABLE_CELLS>::updateNone;
            ptrNoteOn =
                &Tone<NUM_TABLE_CELLS>::noteOnSample;
            ptrNext = &Tone<NUM_TABLE_CELLS>::nextSample;
        } else if (type == SAMPLE_FREQ) {
            ptrUpdate = &Tone<NUM_TABLE_CELLS>::updateFreq;
            ptrNoteOn =
                &Tone<NUM_TABLE_CELLS>::noteOnSampleFreq;
            ptrNext =
                &Tone<NUM_TABLE_CELLS>::nextSampleFreq;
        } else {
            ptrUpdate =
                &Tone<NUM_TABLE_CELLS>::updateSimple;
            ptrNoteOn =
                &Tone<NUM_TABLE_CELLS>::noteOnSimple;
            ptrNext = &Tone<NUM_TABLE_CELLS>::nextSimple;
        }
    }

    void noteOn(int _freqAdd) {
        freqAdd = _freqAdd;
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

    int (Tone<NUM_TABLE_CELLS>::*ptrNext)();
    void (Tone<NUM_TABLE_CELLS>::*ptrUpdate)();
    void (Tone<NUM_TABLE_CELLS>::*ptrNoteOn)();

    void updateNone() {}

    void updateSimple() { envlop.update(); }

    void updateFreq() {
        updateSimple();
        envlopFreq.update();
    }

    void updatePhasor3() {
        updateFreq();
        float resonance_freq = freq() +
                               ((float)(freq()) *
                                ((float)envlopFreq.next() * PDM_SCALE));
        phasorFreq.setFreq(resonance_freq);
    }

    void noteOnSample() {
        sample.setFreq((float)(freq()));
        sample.start();
    }

    void noteOnSampleFreq() {
        noteOnSample();
        envlopFreq.play();
    }

    void noteOnSimple() {
        oscil.setFreq(freq());
        envlop.play();
    }

    void noteOnFreqEnv() {
        noteOnSimple();
        envlopFreq.play();
    }

    void noteOnPhasor() {
        noteOnFreqEnv();
        phasor.setFreq(freq());
        phasorFreq.setFreq(freq());
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
        oscil.setFreq((int)freq() +
                      (envlopFreq.next() >> freqShift));
        return nextSimple();
    }

    int nextSample() { return (int)sample.next() << 8; }

    int nextSampleFreq() {
        sample.setFreq(
            (float)(freq() + (envlopFreq.next() >> freqShift)));
        return nextSample();
    }

    int freq() {
        return frequency + freqAdd;
    }
};

#endif
