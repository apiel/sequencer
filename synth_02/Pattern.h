#ifndef PATTERN_H_
#define PATTERN_H_

#include "Step.h"

#define MAX_STEPS_IN_PATTERN 64

class Pattern {
   public:
    Step steps[MAX_STEPS_IN_PATTERN];

    Pattern() {}

    Pattern* add(byte pos, byte note, byte duration) {
        return add(pos, note, duration, false);
    }

    Pattern* add(byte pos, byte note, byte duration, bool slide) {
        steps[pos].set(note, duration, slide);
        return this;
    }

    // for testing
    void print() {
        for (byte x = 0; x < MAX_STEPS_IN_PATTERN; x++) {
            Serial.print("[");
            Serial.print(x);
            Serial.print(", ");
            Serial.print(steps[x].note);
            Serial.print(", ");
            Serial.print(steps[x].duration);
            Serial.print("],");
            if (x % 8 == 7) {
                Serial.println("");
            }
        }
        Serial.println("\n");
    }

    Pattern* remove(byte pos) {
        steps[pos].clear();
        return this;
    }

    Pattern* clear() {
        for (byte pos = 0; pos < MAX_STEPS_IN_PATTERN; pos++) {
            steps[pos].clear();
        }
        return this;
    }

    Pattern* repeat(byte pos, byte len) {
        return repeat(pos, len, (byte)MAX_STEPS_IN_PATTERN / len);
    }

    Pattern* repeat(byte pos, byte len, byte count) {
        for (byte n = 1; n < count; n++) {
            for (byte p = 0; p < len; p++) {
                steps[pos + n * len + p] = steps[pos + p];
            }
        }
        return this;
    }
};

#endif
