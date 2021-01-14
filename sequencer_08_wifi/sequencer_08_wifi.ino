// http server need to stay on root
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// http server

#include <ADSR.h>
#include <MozziGuts.h>
#include <Oscil.h>  // oscillator template
#include <tables/sin2048_int8.h>
#include <tables/triangle2048_int8.h>
#include <tables/whitenoise8192_int8.h>

#define PIN_SYNC_OUT 27

#define CONTROL_RATE 128  // Hz, powers of 2 are most reliable

#define MAX_PATTERNS 3
#define MAX_NOTES 16  // max # of notes in sequence

#define D_KICK 1
#define D_SNARE 2
#define D_HIHAT 4
#define D_CLAP 8
#define D_CRASH 16
#define D_TOMHI 32

byte gSeqNotes[MAX_PATTERNS][MAX_NOTES] = {
    {D_KICK, 0, D_HIHAT, 0, D_SNARE, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0,
     D_SNARE, 0, D_HIHAT, D_KICK},
    {D_KICK + D_CRASH, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT,
     0, D_CLAP, 0, D_HIHAT, D_KICK},
    {D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0}};

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
    controllerHandler();
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

    // should be at the end to get default values
    controllerSetup();
    setupServer();

    startMozzi(CONTROL_RATE);
}

void loop() { audioHook(); }
