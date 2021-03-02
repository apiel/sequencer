#ifndef TONE_BASE_H_
#define TONE_BASE_H_

#include <Oscil.h>
#include <Phasor.h>
#include <ReverbTank.h>
// #include <Sample.h>

#include "Envelope.h"
#include "Fix_Sample.h"

#define FREQ_ENV_BASE 127

enum { SIMPLE, REVERB, SAMPLE, PHASOR2, PHASOR3, TONE_TYPE_COUNT };

template <uint16_t NUM_TABLE_CELLS, byte ENV_NUM_PHASE, byte ENV_FREQ_NUM_PHASE>
class ToneBase {
   public:
    byte type;
    const char* tableName;
    unsigned int frequency;
    byte freqShift;
    byte phasorShift;

    Sample<NUM_TABLE_CELLS, AUDIO_RATE> sample;

    Envelope<CONTROL_RATE, ENV_NUM_PHASE> envlop{AUDIO_RATE};
    // Envelope<CONTROL_RATE, ENV_NUM_PHASE> envlopFreq{CONTROL_RATE};
    // // before to have PHASOR3 it was AUDIO_RATE
    Envelope<CONTROL_RATE, ENV_FREQ_NUM_PHASE, FREQ_ENV_BASE> envlopFreq{
        AUDIO_RATE};

    ToneBase() : PDM_SCALE(0.05) {
        freqAdd = 0;
        freqShift = 1;
        phasorShift = 21;
        setType(SIMPLE);
    }

    void setType(byte newType) {
        type = newType;
        if (type == REVERB) {
            ptrUpdate = &ToneBase::updateSimple;
            ptrNoteOn = &ToneBase::noteOnSimple;
            ptrNext = &ToneBase::nextReverb;
        } else if (type == PHASOR2) {
            ptrUpdate = &ToneBase::updateSimple;
            ptrNoteOn = &ToneBase::noteOnPhasor;
            ptrNext = &ToneBase::nextPhasor2;
        } else if (type == PHASOR3) {
            ptrUpdate = &ToneBase::updatePhasor3;
            ptrNoteOn = &ToneBase::noteOnPhasor;
            ptrNext = &ToneBase::nextPhasor3;
        } else if (type == SAMPLE) {
            ptrUpdate = &ToneBase::updateSimple;
            ptrNoteOn = &ToneBase::noteOnSample;
            ptrNext = &ToneBase::nextSample;
        } else {
            ptrUpdate = &ToneBase::updateSimple;
            ptrNoteOn = &ToneBase::noteOnSimple;
            ptrNext = &ToneBase::nextSimple;
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

    void setEnvlopFreq(byte index, unsigned int msec, int value) {
        envlopFreq.set(index, msec, FREQ_ENV_BASE + value);
    }

   protected:
    const float PDM_SCALE;
    int freqAdd;

    Oscil<NUM_TABLE_CELLS, AUDIO_RATE> oscil;

    Phasor<AUDIO_RATE> phasor;
    Phasor<AUDIO_RATE> phasorFreq;

    ReverbTank reverb;

    byte previous_counter;

    int (ToneBase::*ptrNext)();
    void (ToneBase::*ptrUpdate)();
    void (ToneBase::*ptrNoteOn)();

    void updateNone() {}

    virtual void updateSimple() {
        envlop.update();
        envlopFreq.update();
    }

    void updatePhasor3() {
        updateSimple();
        float resonance_freq =
            freq() + ((float)(freq()) * ((float)envlopFreq.next() * PDM_SCALE));
        phasorFreq.setFreq(resonance_freq);
    }

    void noteOnSample() {
        sample.setFreq((float)(freq()));
        sample.start();
        envlopFreq.play();
    }

    virtual void noteOnSimple() {
        oscil.setFreq(freq());
        envlop.play();
        envlopFreq.play();
    }

    void noteOnPhasor() {
        noteOnSimple();
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
        oscil.setFreq(nextFreqEnv());
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
        oscil.setFreq(nextFreqEnv());
        return (int)((reverb.next(envlop.next()) * oscil.next()) >> 1);
    }

    int nextSimple() {
        oscil.setFreq(nextFreqEnv());
        return (int)((envlop.next() * oscil.next()) >> 1);
    }

    int nextSample() {
        sample.setFreq((float)nextFreqEnv());
        return (int)sample.next() << 8;
    }

    int nextFreqEnv() {
        int val = (envlopFreq.next() - FREQ_ENV_BASE) >> freqShift;
        return freq() + val;
    }

    int freq() { return frequency + freqAdd; }
};

#endif
