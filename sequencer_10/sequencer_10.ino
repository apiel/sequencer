// http server need to stay on root
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// http server

#include <MozziGuts.h>

// this should be after MozziGuts
#include <EventDelay.h>

#define PIN_SYNC_OUT 27

#define MAX_NOTES 16  // max # of notes in pattern
#define MAX_PATTERNS 3

#define NOTES_COUNT 6  // number of existing notes
#define MENU_SIZE (NOTES_COUNT + 1)

bool gSeqPlay = true;
bool gSeqMute = false;

byte gSeqNoteIndex = 0;
byte gSeqPatternIndex = 0;

EventDelay noteDelay;
byte gBPM = 100;
unsigned int gTempo = 150;

byte gSyncTempo = HIGH;

void handleStepSequencer() {
    // we might need rethink the way to play stop and sync with other device
    if (gSeqPlay) {
        if (noteDelay.ready()) {
            gSeqNoteIndex = (gSeqNoteIndex + 1) % MAX_NOTES;
            gSyncTempo = (gSyncTempo + 1) % 2;
            digitalWrite(PIN_SYNC_OUT, gSyncTempo);

            if (!gSeqMute) {
                playNote();
            }
            noteDelay.start(gTempo);
            // displayUpdate();
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
    if (gSeqPlay && !gSeqMute) {
        return updateAudioSeq();
    }
    return 0;
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_SYNC_OUT, OUTPUT);

    wifiBegin();

    setTempo(gBPM);

    setupNotes();
    displaySetup();
    setupServer();

    startMozzi();
}

void loop() { audioHook(); }
