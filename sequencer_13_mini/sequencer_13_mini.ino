#include <MozziGuts.h>

// this should be after MozziGuts
#include <EventDelay.h>

EventDelay phaseDelay;

unsigned int gTempo = 500;

bool gSeqPlay = true;

void updateControl() {
    if (gSeqPlay) {
        if (phaseDelay.ready()) {
            playPhase();
            phaseDelay.start(gTempo + 500);
        }
        updateEnvelopes();
    }
    handleSerial();
}

int updateAudio() { return gSeqPlay ? updateAudioSeq() : 0; }

void setup() {
    Serial.begin(115200);
    setupPhases();
    startMozzi();
}

void loop() { audioHook(); }
