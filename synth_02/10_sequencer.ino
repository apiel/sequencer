/**
play/stop planning, e.g:
    - play/stop at next sequence
    - play/stop at next middle sequence
    - play/stop at next middle beat
or is this really necessary and instead focus on pattern chaining to achieve
this so everytime we play a sequence we define when it start and for how long
*/

#include "Pattern.h"
#include "Step.h"
#include "note.h"

#define PIN_SYNC_OUT 27
#define MAX_PATTERNS 8
// #define STEP_COUNT MAX_STEPS_IN_PATTERN
#define STEP_COUNT 32
#define STEP_PER_BEAT 4

#define PATTERN_STOP 255

bool gSeqPlay = true;
byte gSeqStepIndex = 0;
byte gBPM = 100;
unsigned int gTempo = 150;
byte gSyncTempo = HIGH;

Pattern patterns[MAX_TONES][MAX_PATTERNS];
byte playingPatterns[MAX_TONES];

void setTempo(byte bpm) {
    gBPM = between(bpm, 10, 255);
    // 4 ♬ ♬ step per beat in 60000ms = 1min
    gTempo = 60000 / (gBPM * STEP_PER_BEAT);
}

void handleStepSequencer() {
    if (gSeqPlay && sequencerClockReady()) {
        gSeqStepIndex = (gSeqStepIndex + 1) % STEP_COUNT;
        gSyncTempo = (gSyncTempo + 1) % 2;
        digitalWrite(PIN_SYNC_OUT, gSyncTempo);
        playStep();
    }
}

void playStep() {
    Tone *pTone;
    Pattern *pPattern;
    for (byte toneId = 0; toneId < MAX_TONES; toneId++) {
        if (playingPatterns[toneId] != PATTERN_STOP) {
            pPattern = &patterns[toneId][playingPatterns[toneId]];
            if (pPattern->steps[gSeqStepIndex].duration) {
                pTone = &tones[toneId];
                pTone->noteOnMs(
                    pPattern->steps[gSeqStepIndex].freqDiff,
                    pPattern->steps[gSeqStepIndex].duration * gTempo -
                        pTone->envlop.getTime(0) - pTone->envlop.getTime(2));
            }
        }
    }
}

void setupSequencer() {
    pinMode(PIN_SYNC_OUT, OUTPUT);
    setTempo(gBPM);

    initDefaultPattern();
    // loadCustomPattern();
}

void initDefaultPattern() {
    for (byte toneId = 0; toneId < MAX_TONES; toneId++) {
        playingPatterns[toneId] = PATTERN_STOP;
        for (byte patternId = 0; patternId < MAX_PATTERNS; patternId++) {
            if (!loadPatternFromStorage(toneId, patternId)) {
                patterns[toneId][patternId].add(0, _C4, 1)->repeat(0, 4);
            }
        }
    }
}

// void loadCustomPattern() {
//     patterns[0][0].clear()->add(0, _C4, 1)->repeat(0, 2)->print();
//     patterns[1][0]
//         .clear()
//         ->add(0, _C0, 1)
//         ->add(1, _D0, 1)
//         ->repeat(0, 2)
//         ->print();
//     patterns[2][0].clear()->add(0, _C4, 8)->repeat(0, 8)->print();
//     patterns[3][0]
//         .clear()
//         // ->add(0, _C4, 6)
//         // ->repeat(0, 8)
//         ->add(0, _C4, 1)
//         ->add(4, _F_4, 1)
//         ->repeat(0, 8)
//         ->add(30, _F4, 1)
//         ->print();
// }
