#include "Step.h"
#include "note.h"

#define PIN_SYNC_OUT 27
#define MAX_PATTERNS 8
// #define STEP_COUNT MAX_STEPS_IN_PATTERN
#define STEP_COUNT 32
// 4 ♬ ♬ step per beat
#define STEP_PER_BEAT 4

#define PATTERN_STOP 255

bool gSeqPlay = true;
byte gSeqStepIndex = 0;
byte gSeqChainIndex = 0;
byte gBPM = 100;
unsigned int gTempo = 150;
byte gSyncTempo = HIGH;

Pattern patterns[MAX_TONES][MAX_PATTERNS];
// should stay like this but at the end of each pattern, it should look
// what are next patterns to play, and update this array
byte playingPatterns[MAX_TONES];

void setTempo(byte bpm) {
    gBPM = between(bpm, 10, 255);
    // 4 ♬ ♬ step per beat in 60000ms = 1min
    gTempo = 60000 / (gBPM * STEP_PER_BEAT);
}

void handleStepSequencer() {
    if (gSeqPlay && sequencerClockReady()) {
        gSeqStepIndex = (gSeqStepIndex + 1) % STEP_COUNT;
        if (gSeqStepIndex == 0) {
            gSeqChainIndex = (gSeqChainIndex + 1) % MAX_CHAINED_PATTERN;
            assignPlayingPatterns();
        }
        gSyncTempo = (gSyncTempo + 1) % 2;
        digitalWrite(PIN_SYNC_OUT, gSyncTempo);
        playStep();
    }
}

void assignPlayingPatterns() {
    Pattern *pPattern;
    for (byte toneId = 0; toneId < MAX_TONES; toneId++) {
        byte priority = 0;
        byte nextPattern = PATTERN_STOP;
        for (byte patternIndex = 0; patternIndex < MAX_PATTERNS;
             patternIndex++) {
            pPattern = &patterns[toneId][patternIndex];
            if (pPattern->counters[gSeqChainIndex] > 0) {
                if (nextPattern == PATTERN_STOP ||
                    pPattern->priority > priority) {
                    priority = pPattern->priority;
                    nextPattern = patternIndex;
                }
            }
        }
        if (nextPattern != PATTERN_STOP) {
            patterns[toneId][nextPattern].counters[gSeqChainIndex]--;
        }
        playingPatterns[toneId] = nextPattern;
        // here need to update display if pattern view
        // in pattern view display current playing pattern
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
    assignPlayingPatterns();
}

void initDefaultPattern() {
    for (byte toneId = 0; toneId < MAX_TONES; toneId++) {
        // playingPatterns[toneId] = PATTERN_STOP;
        for (byte patternId = 0; patternId < MAX_PATTERNS; patternId++) {
            if (!loadPatternFromStorage(toneId, patternId)) {
                patterns[toneId][patternId].add(0, _C4, 1)->repeat(0, 4);
            }
        }
    }
}
