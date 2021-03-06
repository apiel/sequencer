// http server need to stay on root
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// http server

#include <MozziGuts.h>

// this should be after MozziGuts
#include <EventDelay.h>

#define PIN_SYNC_OUT 27

#define STEP_COUNT 16  // count of phases in pattern
#define MAX_PATTERNS 4
#define MAX_PHASES 6  // number of existing phases
#define MENU_SIZE (MAX_PHASES + 1)

#define MAX_VOLUME 127

bool gSeqPlay = true;
byte gVolume = 127;

byte gSeqStepIndex = 0;
byte gSeqPatternIndex = 0;

EventDelay phaseDelay;
byte gBPM = 100;
unsigned int gTempo = 150;

byte gCurrentPhasesSetup = 0;
byte gCurrentPatternId = 0;

byte gSyncTempo = HIGH;

void handleStepSequencer() {
    // we might need rethink the way to play stop and sync with other device
    if (gSeqPlay) {
        if (phaseDelay.ready()) {
            gSeqStepIndex = (gSeqStepIndex + 1) % STEP_COUNT;
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

int updateAudio() { return gSeqPlay ? updateAudioSeq() : 0; }

void setup() {
    Serial.begin(115200);
    pinMode(PIN_SYNC_OUT, OUTPUT);

    wifiBegin();

    setTempo(gBPM);
    assignCurrentPattern(gCurrentPatternId);

    setupPhases(gCurrentPhasesSetup);
    displaySetup();
    setupServer();

    startMozzi();
}

void loop() { audioHook(); }
