#include <MozziGuts.h>
// after MozziGuts
#include <LowPassFilter.h>

#include "Tone.h"

#define MAX_NUM_CELLS 8192
#define MAX_VOLUME 127

#define MAX_TONES 8  // number of existing tones

byte gVolume = MAX_VOLUME;
byte currentTableId = 0;

// seem to be kind of useless
LowPassFilter lpf;
byte gCutoff = 255;
byte gResonance = 0;

Tone tones[MAX_TONES];
Tone* tone;

void updateControl() {
    handleGateIn();
    for (int i = 0; i < MAX_TONES; i++) {
        tones[i].update();
    }
    displayRefresh();
    handleSerial();
}

int updateAudio() {
    int ret = 0;
    for (int i = 0; i < MAX_TONES; i++) {
        ret += tones[i].next();
    }
    return lpf.next((int)(ret * gVolume / MAX_VOLUME)) >> 8;
}

void setup() {
    Serial.begin(115200);

    lpf.setCutoffFreqAndResonance(gCutoff, gResonance);

    // tone = &tones[0];

    // ToDo: load settings from eeprom?
    for (int i = 0; i < MAX_TONES; i++) {
        tone = &tones[i];
        setTable(currentTableId);
        tone->setType(SIMPLE);
        tone->frequency = 30;
        tone->setEnvlop(0, 0, 200);
        tone->setEnvlop(1, 0, 200);
        tone->setEnvlop(2, 300, 0);
    }

    displaySetup();
    startMozzi();
}

void loop() { audioHook(); }
