#ifndef TONE_H_
#define TONE_H_

#include <Oscil.h>
#include <Phasor.h>
#include <ReverbTank.h>
// #include <Sample.h>
#include <EventDelay.h>

#include "Envelope.h"
#include "Fix_Sample.h"

/*
REVERB should be applied on top instead of being a type
think of a way to make it generic
--> doing it in int next() { return (this->*ptrNext)(); } doesnt seem to be
right

having separate type for FREQ env might not be necessary

PHASOR2 is not using envelop Freq, so no need to display it, or even better make
it using it
*/

#define TONE_TYPE_COUNT 5
#define ENV_NUM_PHASE 2
#define ENV_FREQ_NUM_PHASE 3

enum { SIMPLE, REVERB, SAMPLE, PHASOR2, PHASOR3 };

template <uint16_t NUM_TABLE_CELLS>
class Tone {
   public:
    byte type;
    const char* tableName;
    unsigned int frequency;
    byte freqShift;
    byte phasorShift;
    bool substain = true;

    Envelope<CONTROL_RATE, ENV_NUM_PHASE> envlop{AUDIO_RATE};
    // Envelope<CONTROL_RATE, ENV_NUM_PHASE> envlopFreq{CONTROL_RATE};
    // // before to have PHASOR3 it was AUDIO_RATE
    Envelope<CONTROL_RATE, ENV_FREQ_NUM_PHASE> envlopFreq{AUDIO_RATE};

    Tone() : PDM_SCALE(0.05) {
        freqAdd = 0;
        freqShift = 1;
        phasorShift = 21;
        setType(SIMPLE);
    }

    void setType(byte newType) {
        type = newType;
        if (type == REVERB) {
            ptrUpdate = &Tone<NUM_TABLE_CELLS>::updateSimple;
            ptrNoteOn = &Tone<NUM_TABLE_CELLS>::noteOnSimple;
            ptrNext = &Tone<NUM_TABLE_CELLS>::nextReverb;
        } else if (type == PHASOR2) {
            ptrUpdate = &Tone<NUM_TABLE_CELLS>::updateSimple;
            ptrNoteOn = &Tone<NUM_TABLE_CELLS>::noteOnPhasor;
            ptrNext = &Tone<NUM_TABLE_CELLS>::nextPhasor2;
        } else if (type == PHASOR3) {
            ptrUpdate = &Tone<NUM_TABLE_CELLS>::updatePhasor3;
            ptrNoteOn = &Tone<NUM_TABLE_CELLS>::noteOnPhasor;
            ptrNext = &Tone<NUM_TABLE_CELLS>::nextPhasor3;
        } else if (type == SAMPLE) {
            ptrUpdate = &Tone<NUM_TABLE_CELLS>::updateSimple;
            ptrNoteOn = &Tone<NUM_TABLE_CELLS>::noteOnSample;
            ptrNext = &Tone<NUM_TABLE_CELLS>::nextSample;
        } else {
            ptrUpdate = &Tone<NUM_TABLE_CELLS>::updateSimple;
            ptrNoteOn = &Tone<NUM_TABLE_CELLS>::noteOnSimple;
            ptrNext = &Tone<NUM_TABLE_CELLS>::nextSimple;
        }
    }

    void noteOn(int _freqAdd, int ms) {
        if (substain && type != SAMPLE) {
            noteOffDelaySet = true;
            noteOffDelay.start(ms);
        }
        noteOn(_freqAdd);
    }

    void noteOn(int _freqAdd) {
        freqAdd = _freqAdd;
        (this->*ptrNoteOn)();
    }

    void noteOn() {
        freqAdd = 0;
        (this->*ptrNoteOn)();
    }

    // we should unsure that is played only if envelope is used
    void noteOff() {
        envlop.play(1);
        envlopFreq.stopLoop();
        envlopFreq.loop((byte)(envlop.getTime(1) / envlopFreq.getTotalTime()));
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

    EventDelay noteOffDelay;
    bool noteOffDelaySet = false;

    byte previous_counter;

    int (Tone<NUM_TABLE_CELLS>::*ptrNext)();
    void (Tone<NUM_TABLE_CELLS>::*ptrUpdate)();
    void (Tone<NUM_TABLE_CELLS>::*ptrNoteOn)();

    void updateNone() {}

    void updateSimple() {
        if (noteOffDelaySet && noteOffDelay.ready()) {
            noteOffDelaySet = false;
            noteOff();
        }
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

    void noteOnSimple() {
        oscil.setFreq(freq());
        if (substain) {
            envlop.play(0, 1);
        } else {
            envlop.play();
        }
        envlopFreq.loop();
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
        oscil.setFreq((int)freq() + (envlopFreq.next() >> freqShift));
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
        oscil.setFreq((int)freq() + (envlopFreq.next() >> freqShift));
        return (int)((reverb.next(envlop.next()) * oscil.next()) >> 1);
    }

    int nextSimple() {
        oscil.setFreq((int)freq() + (envlopFreq.next() >> freqShift));
        return (int)((envlop.next() * oscil.next()) >> 1);
    }

    int nextSample() {
        sample.setFreq((float)(freq() + (envlopFreq.next() >> freqShift)));
        return (int)sample.next() << 8;
    }

    int freq() { return frequency + freqAdd; }
};

#endif
