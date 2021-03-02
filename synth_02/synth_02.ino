#include <MozziGuts.h>
// after MozziGuts
#include <LowPassFilter.h>

#include "Tone.h"

#define MAX_NUM_CELLS 8192
#define MAX_VOLUME 127

byte gVolume = MAX_VOLUME;
byte currentTableId = 0;

// seem to be kind of useless
LowPassFilter lpf;
byte gCutoff = 255;
byte gResonance = 0;

Tone tone;

void updateControl() {
    handleGateIn();
    tone.update();
    displayRefresh();
    handleSerial();
}

int updateAudio() {
    return lpf.next((int)(tone.next() * gVolume / MAX_VOLUME)) >> 8;
}

void setup() {
    Serial.begin(115200);

    setTable(currentTableId);
    lpf.setCutoffFreqAndResonance(gCutoff, gResonance);
    tone.setType(SIMPLE);
    tone.frequency = 100;
    // tone.setEnvlop(0, 50, 200);
    // tone.setEnvlop(1, 50, 200);
    // tone.setEnvlop(2, 100, 0);
    tone.setEnvlop(0, 0, 200);
    tone.setEnvlop(1, 0, 200);
    tone.setEnvlop(2, 300, 0);
    // tone.setEnvlopFreq(0, 50, 70);
    // tone.setEnvlopFreq(1, 50, 120);
    // tone.setEnvlopFreq(2, 50, 50);

    // tone.setEnvlopFreq(0, 50, 0);
    // tone.setEnvlopFreq(1, 50, 0);
    // tone.setEnvlopFreq(2, 50, 0);
    // tone.setEnvlopFreq(3, 0, 0);
    // tone.setEnvlopFreq(4, 0, 0);
    // tone.setEnvlopFreq(5, 50, 0);

    displaySetup();
    startMozzi();
}

void loop() { audioHook(); }
