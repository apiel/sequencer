// http server need to stay on root
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// http server

#include <MozziGuts.h>

// this should be after MozziGuts
#include <EventDelay.h>

#define PIN_SYNC_OUT 27

#define MAX_PHASES 16  // max # of phases in pattern
#define MAX_PATTERNS 3

#define PHASES_COUNT 6  // number of existing phases
#define MENU_SIZE (PHASES_COUNT + 1)

#define MAX_VOLUME 127

bool gSeqPlay = true;
byte gVolume = 127;

byte gSeqPhaseIndex = 0;
byte gSeqPatternIndex = 0;

EventDelay phaseDelay;
byte gBPM = 100;
unsigned int gTempo = 150;

byte gSyncTempo = HIGH;

void handleStepSequencer() {
    // we might need rethink the way to play stop and sync with other device
    if (gSeqPlay) {
        if (phaseDelay.ready()) {
            gSeqPhaseIndex = (gSeqPhaseIndex + 1) % MAX_PHASES;
            gSyncTempo = (gSyncTempo + 1) % 2;
            digitalWrite(PIN_SYNC_OUT, gSyncTempo);
            playPhase();
            phaseDelay.start(gTempo);
        }
        updateEnvelopes();
    }
}

void updateControl() {
    wifiCheck();
    handleStepSequencer();
    displayUpdate();
}

int updateAudio() {
    return gSeqPlay ? updateAudioSeq() : 0;
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_SYNC_OUT, OUTPUT);

    wifiBegin();

    setTempo(gBPM);

    setupPhases();
    displaySetup();
    setupServer();

    startMozzi();
}

void loop() { audioHook(); }
