#include <EventDelay.h>

#define GATE_IN_PIN 33

enum { INTERNAL_CLOCK, GATE_IN_CLOCK, CLOCK_COUNT };

byte currentClock = INTERNAL_CLOCK;

bool gateTriggered = false;

EventDelay stepDelay;

bool sequencerClockReady() { return internalClock() || gateInClock(); }

bool gateInClock() {
    if (currentClock == GATE_IN_CLOCK) {
        if (analogRead(GATE_IN_PIN) > 0) {
            if (!gateTriggered) {
                gateTriggered = true;
                return true;  // noteOn
            }
        } else {
            gateTriggered = false;
        }
    }
    return false;
}

bool internalClock() {
    if (currentClock == INTERNAL_CLOCK && stepDelay.ready()) {
        stepDelay.start(gTempo);
        return true;  // noteOn
    }
    return false;
}
