// http server need to stay on root
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// http server

#include <MozziGuts.h>

// this should be after MozziGuts
#include <EventDelay.h>

#define PIN_SYNC_OUT 27

#define MAX_DRUMS 16  // max # of drums in pattern
#define MAX_PATTERNS 3

#define DRUMS_COUNT 6  // number of existing drums
#define MENU_SIZE (DRUMS_COUNT + 1)

#define MAX_VOLUME 127

bool gSeqPlay = true;
byte gVolume = 127;

byte gSeqDrumIndex = 0;
byte gSeqPatternIndex = 0;

EventDelay drumDelay;
byte gBPM = 100;
unsigned int gTempo = 150;

byte gSyncTempo = HIGH;

void handleStepSequencer() {
    // we might need rethink the way to play stop and sync with other device
    if (gSeqPlay) {
        if (drumDelay.ready()) {
            gSeqDrumIndex = (gSeqDrumIndex + 1) % MAX_DRUMS;
            gSyncTempo = (gSyncTempo + 1) % 2;
            digitalWrite(PIN_SYNC_OUT, gSyncTempo);
            playDrum();
            drumDelay.start(gTempo);
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
    if (gSeqPlay) {
        return updateAudioSeq();
    }
    return 0;
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_SYNC_OUT, OUTPUT);

    wifiBegin();

    setTempo(gBPM);

    setupDrums();
    displaySetup();
    setupServer();

    startMozzi();
}

void loop() { audioHook(); }
