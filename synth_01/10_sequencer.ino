/**
create a list of sequences with different pitch
a sequence is assign to one instrument/tone (should it be multple output?)
*/

#include <EventDelay.h>

#include "Pattern.h"
#include "Step.h"
#include "note.h"

#define PIN_SYNC_OUT 27
#define MAX_PATTERNS 4
#define STEP_COUNT MAX_STEPS_IN_PATTERN

EventDelay stepDelay;

bool gSeqPlay = true;
byte gSeqStepIndex = 0;
byte gBPM = 100;
byte gSyncTempo = HIGH;

Pattern patterns[MAX_PATTERNS];

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

    patterns[0].set((char *)"Kick", 0)->add(0, _C4, 1)->repeat(0, 4)->print();
    // patterns[0].play();
    patterns[1]
        .set((char *)"Bass", 2)
        ->add(0, _C4, 1)
        ->add(1, _D4, 1)
        ->repeat(0, 2)
        ->print();
    patterns[2].set((char *)"Phasor", 5)->add(0, _C4, 1)->repeat(0, 8)->print();
    patterns[3]
        .set((char *)"Kick2", 1)
        ->add(0, _C4, 1)
        ->add(4, _F4, 1)
        ->repeat(0, 8)
        ->add(62, _D4, 1)
        ->print();
    patterns[3].play();
}

void playStep() {
    for (int p = 0; p < MAX_PATTERNS; p++) {
        if (patterns[p].isPlaying &&
            patterns[p].steps[gSeqStepIndex].duration) {
            tones[patterns[p].outputId].noteOn(
                patterns[p].steps[gSeqStepIndex].freqDiff);

            // ToDo: use duration
            // think about substain and release (noteOff())
        }
    }
}

// Actions

// void toggleTone(byte toneIdx, byte pos) {
//     int aTone = gCurrentPattern[pos];
//     int powTone = pow(2, toneIdx);
//     if (aTone & powTone) {
//         gCurrentPattern[pos] -= powTone;
//     } else {
//         gCurrentPattern[pos] += powTone;
//     }
// }

// void setStepPattern(byte step, int val) { gCurrentPattern[step] = val; }

// void assignCurrentPattern(byte index) {
//     gCurrentPatternId = index % MAX_PATTERNS;
//     for (int i = 0; i < STEP_COUNT; i++) {
//         gCurrentPattern[i] = gSeqTones[gCurrentPatternId][i];
//     }
// }