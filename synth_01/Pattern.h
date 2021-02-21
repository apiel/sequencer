#ifndef PATTERN_H_
#define PATTERN_H_

#include "Step.h"

#define MAX_STEPS_IN_PATTERN 64

class Pattern {
   public:
    char* name = (char*)"default";
    Step steps[MAX_STEPS_IN_PATTERN];

    Pattern() {}
    Pattern(const char* ptrName) { name = (char*)ptrName; }

    Pattern setName(char* ptrName) {
        name = ptrName;
        return *this;
    }

    Pattern add(byte pos, byte note, byte duration) {
        return add(pos, note, duration, false);
    }

    Pattern add(byte pos, byte note, byte duration, bool slide) {
        steps[pos].note = note;
        steps[pos].duration = duration;
        steps[pos].slide = slide;
        return *this;
    }

    Pattern remove(byte pos) {
        steps[pos].clear();
        return *this;
    }
};

#endif
