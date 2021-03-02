#define GATE_IN_PIN 33

// here we could do something to trigger sound only every 4 step
// but behringer crave allow to do this from assign

bool gateTriggered = false;

void handleGateIn() {
    if (analogRead(GATE_IN_PIN) > 0) {
        if (!gateTriggered) {
            gateTriggered = true;
            tone->noteOn();
        }
    } else {
        gateTriggered = false;
    }
}