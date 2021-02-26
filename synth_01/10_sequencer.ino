/**
play/stop planning, e.g:
    - play/stop at next sequence
    - play/stop at next middle sequence
    - play/stop at next middle beat
or is this really necessary and instead focus on pattern chaining to achieve
this so everytime we play a sequence we define when it start and for how long
*/

#include <EventDelay.h>

#include "Pattern.h"
#include "Step.h"
#include "note.h"

#define PIN_SYNC_OUT 27
#define MAX_PATTERNS 4
#define STEP_COUNT MAX_STEPS_IN_PATTERN
#define STEP_PER_BEAT 4

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

    patterns[0].set((char *)"Kick", TONE_A)->add(0, _C4, 1)->repeat(0, 2)->print();
    // patterns[0].play();
    patterns[1]
        .set((char *)"Bass", TONE_E)
        ->add(0, _C0, 1)
        ->add(1, _D0, 1)
        ->repeat(0, 2)
        ->print();
    patterns[2].set((char *)"Phasor", TONE_F)->add(0, _C4, 8)->repeat(0, 8)->print();
    patterns[3]
        .set((char *)"Kick2", TONE_B)
        // ->add(0, _C4, 6)
        // ->repeat(0, 8)
        ->add(0, _C4, 1)
        ->add(4, _F_4, 1)
        ->repeat(0, 8)
        ->add(62, _F4, 1)
        ->print();
    patterns[3].play();
}

void playStep() {
    Tone<MAX_NUM_CELLS> *tone;
    for (int p = 0; p < MAX_PATTERNS; p++) {
        if (patterns[p].isPlaying &&
            patterns[p].steps[gSeqStepIndex].duration) {
            tone = &tones[patterns[p].outputId];
            tone->noteOn(patterns[p].steps[gSeqStepIndex].freqDiff,
                         patterns[p].steps[gSeqStepIndex].duration * gTempo -
                             tone->envlop.getTime(0) - tone->envlop.getTime(2));
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