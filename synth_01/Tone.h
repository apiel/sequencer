#ifndef TONE_H_
#define TONE_H_

#include <EventDelay.h>

#include "ToneBase.h"

/*
REVERB should be applied on top instead of being a type
think of a way to make it generic
--> doing it in int next() { return (this->*ptrNext)(); } doesnt seem to be
right

having separate type for FREQ env might not be necessary

PHASOR2 is not using envelop Freq, so no need to display it, or even better make
it using it
*/

class Tone : public ToneBase {
   public:
    bool substain = true;

    void noteOnMs(int _freqAdd, int ms) {
        if (substain && this->type != SAMPLE) {
            noteOffDelaySet = true;
            noteOffDelay.start(ms);
        }
        this->noteOn(_freqAdd);
    }

    // we should unsure that is played only if envelope is used
    void noteOff() {
        if (substain && this->type != SAMPLE) {
            this->envlop.play(1);
            this->envlopFreq.stopLoop();
            this->envlopFreq.loop((byte)(this->envlop.getTime(1) /
                                         this->envlopFreq.getTotalTime()));
        }
    }

   protected:
    EventDelay noteOffDelay;
    bool noteOffDelaySet = false;

    // using ToneBase::updateSimple;
    void updateSimple() {
        if (noteOffDelaySet && noteOffDelay.ready()) {
            noteOffDelaySet = false;
            noteOff();
        }
        this->envlop.update();
        this->envlopFreq.update();
    }

    // using ToneBase::noteOnSimple;
    void noteOnSimple() {
        this->oscil.setFreq(this->freq());
        if (substain) {
            this->envlop.play(0, 1);
        } else {
            this->envlop.play();
        }
        this->envlopFreq.loop();
        this->envlopFreq.play();
    }
};

#endif
