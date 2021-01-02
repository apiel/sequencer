#include <ADSR.h>
#include <MozziGuts.h>
#include <Oscil.h>  // oscillator template
#include <tables/sin2048_int8.h>
#include <tables/triangle2048_int8.h>
#include <tables/whitenoise8192_int8.h>

#define CONTROL_RATE 128  // Hz, powers of 2 are most reliable

#define MAX_NOTES 16  // max # of notes in sequence
#define D_KICK 1
#define D_SNARE 2
#define D_HIHAT 4
#define D_CLAP 8
#define D_CRASH 16
#define D_TOMHI 32

byte gSeqNotes[MAX_NOTES] = {D_KICK,  0, D_HIHAT, 0,     D_SNARE, 0,
                             D_HIHAT, 0, D_KICK,  0,     D_HIHAT, 0,
                             D_SNARE, 0, D_HIHAT, D_KICK};

int gSelected = 0;
bool gSeqNoteOn = false;
bool gSyncNoteOn = false;

byte gSeqNoteIndex = 0;

typedef struct {
    uint8_t gSeqGatePercent;
    byte gSeqBPM;          // tempo, BPM (beats per minute)
    unsigned int gSeqT16;  // length in ms of 1/16
} SeqBase;

SeqBase gSeqBase;

unsigned long gSeqTimeCurrent;
unsigned long gSeqTimeLast;
unsigned long gSeqTimeGate;

void setTempo() {
    gSeqBase.gSeqT16 = 1000 / ((gSeqBase.gSeqBPM * 4) / ((float)60));
}

void calcGate() {
    gSeqTimeGate = (gSeqBase.gSeqT16 * gSeqBase.gSeqGatePercent) / 100;
}

void updateControl() {
    gSeqTimeCurrent = millis();
    if ((gSeqTimeCurrent - gSeqTimeLast >= gSeqBase.gSeqT16) && !gSeqNoteOn) {
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
        playNote();
        // Serial.println("should play note");
        gSyncNoteOn = false;
    }

    if (gSeqTimeCurrent - gSeqTimeLast >= gSeqTimeGate) {
        gSeqNoteOn = false;
    }
    updateEnvelopes();
}

int updateAudio() {
    return updateAudioSeq();
}

void setup() {
    Serial.begin(115200);

    gSeqBase.gSeqBPM = 120;  // tempo, BPM (beats per minute)
    gSeqBase.gSeqGatePercent = 50;
    setTempo();
    calcGate();

    gSeqTimeCurrent = millis();
    gSeqTimeLast = gSeqTimeCurrent;

    setupNotes();

    startMozzi(CONTROL_RATE);
}

void loop() { audioHook(); }
