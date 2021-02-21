#ifndef STEP_H_
#define STEP_H_

#include "note.h"


#define BASE_FREQ _C4

class Step {
   public:
    byte note = 0;
    byte duration = 0;
    // byte velocity;
    bool slide = false;
    int freqDiff = 0;

    Step() {}

    void clear() {
        note = 0;
        duration = 0;
    }

    void set(byte _note, byte _duration, bool _slide) {
        note = _note;
        duration = _duration;
        slide = _slide;
        freqDiff = NOTE_FREQ[BASE_FREQ] - NOTE_FREQ[note];
    }

    // Step(byte _note, byte _duration, bool _slide) {
    //     note = _note;
    //     duration = _duration;
    //     slide = _slide;
    // }
};

#endif
