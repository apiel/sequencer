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
    displayRefresh();
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
    kick.setEnvlopFreq(0, 50, 70);
    kick.setEnvlopFreq(1, 50, 120);
    kick.setEnvlopFreq(2, 50, 50);
    kick.setEnvlopFreq(3, 0, 0);
    kick.setEnvlopFreq(4, 0, 0);
    kick.setEnvlopFreq(5, 50, 0);

    displaySetup();
    startMozzi();
}

void loop() { audioHook(); }
