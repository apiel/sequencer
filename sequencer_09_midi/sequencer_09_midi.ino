// http server need to stay on root
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// http server

#include <MozziGuts.h>

#define PIN_SYNC_OUT 27

#define CONTROL_RATE 128  // Hz, powers of 2 are most reliable
#define MAX_NOTES 16  // max # of notes in pattern
#define MAX_PATTERNS 3

#define NOTES_COUNT 6 // number of existing notes
#define MENU_SIZE (NOTES_COUNT + 1)

bool gSeqNoteOn = false;
bool gSeqPlay = true;
bool gSeqMute = false;
bool gSyncNoteOn = false;

byte gSeqNoteIndex = 0;
byte gSeqPatternIndex = 0;

typedef struct {
    uint8_t gSeqGatePercent;
    byte gSeqBPM;          // tempo, BPM (beats per minute)
    unsigned int gSeqT16;  // length in ms of 1/16
} SeqBase;

SeqBase gSeqBase;

// should we use EventDelay instead?
// see
// https://github.com/sensorium/Mozzi/blob/master/examples/07.Envelopes/ADSR_Audio_Rate_Envelope/ADSR_Audio_Rate_Envelope.ino
unsigned long gSeqTimeCurrent;
unsigned long gSeqTimeLast;
unsigned long gSeqTimeGate;

void setTempo() {
    gSeqBase.gSeqT16 = 1000 / ((gSeqBase.gSeqBPM * 4) / ((float)60));
}

void calcGate() {
    gSeqTimeGate = (gSeqBase.gSeqT16 * gSeqBase.gSeqGatePercent) / 100;
}

byte gSyncTempo = HIGH;

void handleStepSequencer() {
    if (gSeqPlay) {
        gSeqTimeCurrent = millis();
        if ((gSeqTimeCurrent - gSeqTimeLast >= gSeqBase.gSeqT16) &&
            !gSeqNoteOn) {
            // gSyncNoteOn should not be necessary, we could run playNote
            // directly there
            gSyncNoteOn = true;
            gSeqTimeLast = gSeqTimeLast + gSeqBase.gSeqT16;
        } else {
            gSyncNoteOn = false;
        }

        if (gSyncNoteOn) {
            gSeqNoteIndex++;
            if (gSeqNoteIndex >= MAX_NOTES) {
                gSeqNoteIndex = 0;
            }
            gSyncTempo = (gSyncTempo + 1) % 2;
            digitalWrite(PIN_SYNC_OUT, gSyncTempo);
            if (!gSeqMute) {
                playNote();
            }
            gSyncNoteOn = false;
        }

        if (gSeqTimeCurrent - gSeqTimeLast >= gSeqTimeGate) {
            gSeqNoteOn = false;
        }
        updateEnvelopes();
    }
}

void updateControl() {
    wifiCheck();
    handleStepSequencer();
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

    gSeqBase.gSeqBPM = 120;  // tempo, BPM (beats per minute)
    gSeqBase.gSeqGatePercent = 50;
    setTempo();
    calcGate();

    gSeqTimeCurrent = millis();
    gSeqTimeLast = gSeqTimeCurrent;

    setupNotes();

    displaySetup();
    setupServer();

    startMozzi(CONTROL_RATE);
}

void loop() { audioHook(); }
