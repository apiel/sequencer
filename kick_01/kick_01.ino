#include <MozziGuts.h>
// after MozziGuts
#include <LowPassFilter.h>

#include "Kick.h"

#define MAX_NUM_CELLS 8192
#define MAX_VOLUME 127

byte gVolume = MAX_VOLUME;
byte currentTableId = 0;

// seem to be kind of useless
LowPassFilter lpf;
byte gCutoff = 255;
byte gResonance = 0;

Kick kick;

void updateControl() {
    kick.update();
    displayUpdate();
    handleSerial();
}

int updateAudio() {
    return lpf.next((int)(kick.next() *gVolume / MAX_VOLUME)) >> 8;
}

void setup() {
    Serial.begin(115200);

    setTable(currentTableId);
    lpf.setCutoffFreqAndResonance(gCutoff, gResonance);
    kick.setType(SIMPLE);
    kick.frequency = 100;
    kick.envlop.set(0, 50, 200);
    kick.envlop.set(1, 50, 200);
    kick.envlop.set(2, 100, 0);
    kick.envlopFreq.set(0, 50, 150);
    kick.envlopFreq.set(1, 50, 200);
    kick.envlopFreq.set(2, 50, 100);

    displaySetup();
    startMozzi();
}

void loop() { audioHook(); }
