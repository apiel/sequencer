#ifndef STEP_H_
#define STEP_H_

#include "note.h"


#define BASE_FREQ _C4

class Step {
   public:
    byte note;
    byte duration;
    // byte velocity;
    bool slide;

    Step() { clear(); }

    void clear() {
        note = 0;
        duration = 0;
        slide = false;
    }

    int getFreqDiff() {
        return NOTE_FREQ[BASE_FREQ] - NOTE_FREQ[note];
    }

    // Step(byte _note, byte _duration, bool _slide) {
    //     note = _note;
    //     duration = _duration;
    //     slide = _slide;
    // }
};

#endif
