#ifndef STEP_H_
#define STEP_H_

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

    // Step(byte _note, byte _duration, bool _slide) {
    //     note = _note;
    //     duration = _duration;
    //     slide = _slide;
    // }
};

#endif
