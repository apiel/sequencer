/**
create a list of sequences with different pitch
a sequence is assign to one instrument/tone (should it be multple output?)
*/

#include <EventDelay.h>
#include "note.h"

#define PIN_SYNC_OUT 27

#define MAX_PATTERNS 4

#define TONE_A 1
#define TONE_B 2
#define TONE_C 4
#define TONE_D 8
#define TONE_E 16
#define TONE_F 32

bool gSeqPlay = true;

byte gSeqStepIndex = 0;
byte gSeqPatternIndex = 0;

EventDelay stepDelay;
byte gBPM = 100;

byte gCurrentPatternId = 0;

byte gSyncTempo = HIGH;

byte gSeqTones[MAX_PATTERNS][STEP_COUNT] = {
    {TONE_A, 0, 0, 0, TONE_B, 0, 0, 0, TONE_A, 0, 0, 0, TONE_B, 0, 0, TONE_A},
    {TONE_A + TONE_E, 0, TONE_C, 0, TONE_A, 0, TONE_C, 0, TONE_A, 0, TONE_C, 0,
     TONE_D, 0, TONE_C, TONE_A},
    {TONE_A, 0, 0, 0, TONE_A, 0, 0, 0, TONE_A, 0, 0, 0, TONE_A, 0, 0, 0},
    {TONE_F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

byte gCurrentPattern[STEP_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0};

void handleStepSequencer() {
    if (gSeqPlay && stepDelay.ready()) {
        gSeqStepIndex = (gSeqStepIndex + 1) % STEP_COUNT;
        gSyncTempo = (gSyncTempo + 1) % 2;
        digitalWrite(PIN_SYNC_OUT, gSyncTempo);
        playStep();
        stepDelay.start(gTempo);
    }
}

void setupSequencer() {
    // Serial.print("C4 freq: ");
    // Serial.println(NOTE_FREQ[_C4]);

    pinMode(PIN_SYNC_OUT, OUTPUT);
    setTempo(gBPM);
    assignCurrentPattern(gCurrentPatternId);
}

void playStep() {
    int aTone = gCurrentPattern[gSeqStepIndex];

    for (int i = 0; i < MAX_TONES; i++) {
        if (aTone & (int)pow(2, i)) {
            tones[i].noteOn(gSeqStepIndex);
        }
    }
}

// Actions

void toggleTone(byte toneIdx, byte pos) {
    int aTone = gCurrentPattern[pos];
    int powTone = pow(2, toneIdx);
    if (aTone & powTone) {
        gCurrentPattern[pos] -= powTone;
    } else {
        gCurrentPattern[pos] += powTone;
    }
}

void setStepPattern(byte step, int val) { gCurrentPattern[step] = val; }

void assignCurrentPattern(byte index) {
    gCurrentPatternId = index % MAX_PATTERNS;
    for (int i = 0; i < STEP_COUNT; i++) {
        gCurrentPattern[i] = gSeqTones[gCurrentPatternId][i];
    }
}