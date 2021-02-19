#include <MozziGuts.h>

// this should be after MozziGuts
#include <EventDelay.h>

EventDelay phaseDelay;

unsigned int gTempo = 500;

bool gSeqPlay = true;

void updateControl() {
    // important change here! keep updating the envelop
    // even if seq play is false so we can play synth with keyboard
    if (gSeqPlay) {
        if (phaseDelay.ready()) {
            playPhase();
            phaseDelay.start(gTempo + 500);
        }
    }
    updateEnvelopes();
    handleSerial();
}

int updateAudio() { return updateAudioSeq(); }

void setup() {
    Serial.begin(115200);
    setupPhases();
    startMozzi();
}

void loop() { audioHook(); }
