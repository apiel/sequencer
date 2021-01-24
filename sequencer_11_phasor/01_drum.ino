/*
Make the frequency adsr table independent from the main adsr
So the frequency adsr doesnt have to be the same...

when pressing loop the pattern button become synth

Look at PDResonant it seem awesome :p
Look at synth in general:
- FMsynth
- WaveShaper?
*/

// #include <AudioDelay.h>
#include <LowPassFilter.h>

// #include <ADSR.h>
#include "Phase.h"

#define D_KICK 1
#define D_SNARE 2
#define D_HIHAT 4
#define D_CLAP 8
#define D_CRASH 16
#define D_TOMHI 32

#define MAX_NUM_CELLS 8192

// AudioDelay<256> audioDelay;
// byte gDelayValue = 255;

// seem to be kind of useless
LowPassFilter lpf;
byte gCutoff = 255;
byte gResonance = 0;

byte currentTableId = 0;

byte gSeqDrums[MAX_PATTERNS][MAX_DRUMS] = {
    {D_KICK, 0, D_HIHAT, 0, D_SNARE, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0,
     D_SNARE, 0, D_HIHAT, D_KICK},
    {D_KICK + D_CRASH, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT,
     0, D_CLAP, 0, D_HIHAT, D_KICK},
    {D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0}};

byte gCurrentPattern[MAX_DRUMS] = {0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0};

byte gCurrentPatternId = 0;

Phase<MAX_NUM_CELLS> phases[DRUMS_COUNT];

void toggleDrum(byte drum, byte pos) {
    int aDrum = gCurrentPattern[pos];
    int powDrum = pow(2, drum);
    if (aDrum & powDrum) {
        gCurrentPattern[pos] -= powDrum;
    } else {
        gCurrentPattern[pos] += powDrum;
    }
}

void setDrumFromMidiBtn(byte drum, byte optionKey) {
    if (optionKey == 0) {
        // ToDo change phase type
        // gDrum[drum].useFreqEnvelope = !gDrum[drum].useFreqEnvelope;
    } else if (optionKey == 1) {
        if (phases[drum].freqShift > 0) {
            phases[drum].freqShift--;
        }
    } else if (optionKey == 2) {
        if (phases[drum].freqShift < 16) {
            phases[drum].freqShift++;
        }
    }
}

void setDrumFromMidiKnob(byte drum, byte optionKey, int direction) {
    Serial.print("setDrumFromMidi: ");
    Serial.print(drum);
    Serial.print(" key: ");
    Serial.print(optionKey);
    Serial.print(" dir: ");
    Serial.println(direction);

    // ToDo...

    // if (optionKey == 2) {
    //     currentTableId = mod(currentTableId + direction, 24);
    //     setTable(drum, currentTableId);
    // } else if (optionKey == 3) {
    //     gDrum[drum].PeakLevel =
    //         between(gDrum[drum].PeakLevel + direction, 0, 250);
    // } else if (optionKey == 4) {
    //     gDrum[drum].SustainLevel =
    //         between(gDrum[drum].SustainLevel + direction, 0, 250);
    // } else if (optionKey == 5) {
    //     gDrum[drum].ATime = between(gDrum[drum].ATime + direction, 0, 100);
    // } else if (optionKey == 6) {
    //     gDrum[drum].DTime = between(gDrum[drum].DTime + direction, 0, 100);
    // } else if (optionKey == 7) {
    //     gDrum[drum].STime = between(gDrum[drum].STime + direction, 0, 100);
    // } else if (optionKey == 8) {
    //     gDrum[drum].RTime = between(gDrum[drum].RTime + direction, 0, 100);
    // } else if (optionKey == 12) {
    //     gDrum[drum].frequency =
    //         between(gDrum[drum].frequency + direction, 0, 2000);
    // } else if (optionKey == 13) {
    //     gDrum[drum].AFreqLevel =
    //         between(gDrum[drum].AFreqLevel + direction, 0, 255);
    // } else if (optionKey == 14) {
    //     gDrum[drum].SFreqLevel =
    //         between(gDrum[drum].SFreqLevel + direction, 0, 255);
    // } else if (optionKey == 15) {
    //     gDrum[drum].RFreqLevel =
    //         between(gDrum[drum].RFreqLevel + direction, 0, 255);
    // } else if (optionKey == 16) {
    //     gDrum[drum].AFreqTime =
    //         between(gDrum[drum].AFreqTime + direction, 0, 100);
    // } else if (optionKey == 17) {
    //     gDrum[drum].SFreqTime =
    //         between(gDrum[drum].SFreqTime + direction, 0, 100);
    // } else if (optionKey == 18) {
    //     gDrum[drum].RFreqTime =
    //         between(gDrum[drum].RFreqTime + direction, 0, 100);
    // }

    // if (optionKey != 2 && optionKey != 12) {
    //     applySetting(drum);
    // }
}

void playDrum() {
    int aDrum = gCurrentPattern[gSeqDrumIndex];

    for (int i = 0; i < DRUMS_COUNT; i++) {
        if (aDrum & (int)pow(2, i)) {
            phases[i].noteOn();
        }
    }
}

void setStepPattern(byte step, int val) { gCurrentPattern[step] = val; }

void assignCurrentPattern(byte index) {
    gCurrentPatternId = index % MAX_PATTERNS;
    for (int i = 0; i < MAX_DRUMS; i++) {
        gCurrentPattern[i] = gSeqDrums[gCurrentPatternId][i];
    }
}

byte getCurrentPatternId() { return gCurrentPatternId; }

void setupDrum(byte drum, byte tableId, bool useFreqEnvelope, int frequency) {
    setTable(drum, tableId);

    lpf.setCutoffFreqAndResonance(gCutoff, gResonance);

    // phases[drum].type = PHASOR;  // todo configurable
    phases[drum].type = FREQ_ENV;  // todo configurable
    // phases[drum].type = SIMPLE; // todo configurable
    phases[drum].frequency = frequency;

    phases[drum].adsr.setTimes(0, 0, 0, gTempo);
    phases[drum].adsr.setLevels(250, 200, 200, 0);

    phases[drum].adsrFreq.setTimes(0, 0, 0, gTempo);
    phases[drum].adsrFreq.setLevels(200, 200, 200, 0);
    phases[drum].freqShift = 1;
}

// ToDo
// void applySetting(byte drum) {
//     gDrum[drum].adsr.setLevels(gDrum[drum].PeakLevel,
//     gDrum[drum].SustainLevel,
//                                gDrum[drum].SustainLevel, 0);
//     gDrum[drum].adsr.setTimes(
//         gTempo / 100 * gDrum[drum].ATime, gTempo / 100 * gDrum[drum].DTime,
//         gTempo / 100 * gDrum[drum].STime, gTempo / 100 * gDrum[drum].RTime);

//     gDrum[drum].adsrFreq.setLevels(
//         gDrum[drum].AFreqLevel, gDrum[drum].AFreqLevel,
//         gDrum[drum].SFreqLevel, gDrum[drum].RFreqLevel);
//     gDrum[drum].adsrFreq.setTimes(gTempo / 100 * gDrum[drum].AFreqTime, 0,
//                                   gTempo / 100 * gDrum[drum].SFreqTime,
//                                   gTempo / 100 * gDrum[drum].RFreqTime);
// }

void setupDrums() {
    assignCurrentPattern(gCurrentPatternId);

    setupDrum(0, 20, true, 45);
    setupDrum(1, 20, true, 150);
    setupDrum(2, 10, false, 100);
    setupDrum(3, 10, false, 0);
    setupDrum(4, 10, false, 0);
    setupDrum(5, 2, true, 100);
}

void updateEnvelopes() {
    for (int i = 0; i < DRUMS_COUNT; i++) {
        phases[i].update();
    }
}

int updateAudioSeq() {
    int ret = 0;
    for (int i = 0; i < DRUMS_COUNT; i++) {
        ret += phases[i].next();
    }

    // return ret >> 8;
    return lpf.next((int)(ret * gVolume / MAX_VOLUME)) >> 8;
    // return audioDelay.next(lpf.next((int)(ret * gVolume / MAX_VOLUME)),
    // gDelayValue) >> 8;
    // return (int)(ret * gVolume / MAX_VOLUME) >> 8;
}


void increaseCutoff(int direction) {
    gCutoff = (byte)between(gCutoff + (direction * 2), 0, 255);
    lpf.setCutoffFreq(gCutoff);
    // Serial.print("Set gCutoff ");
    // Serial.println(gCutoff);
}

void increaseResonance(int direction) {
    gResonance = (byte)between(gResonance + (direction * 2), 0, 255);
    lpf.setResonance(gResonance);
    // Serial.print("Set gResonance ");
    // Serial.println(gResonance);
}

void displayLpf() {
    dprintln("Cutoff: %d", gCutoff);
    dprintln("Resonance: %d", gResonance);
}
