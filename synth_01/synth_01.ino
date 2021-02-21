#include <MozziGuts.h>

#define MAX_TONES 6  // number of existing tones
#define MENU_SIZE (MAX_TONES + 1)

#define MAX_VOLUME 127

byte gVolume = 127;

// gTempo is related to sequencer
// but tone need to know about it, to be able to calculate envelop timing
// ToDo see if there would be way to do differently
unsigned int gTempo = 150;

byte gCurrentTonesSetup = 0;

void updateControl() {
    updateEnvelopes();
    handleStepSequencer();
    displayUpdate();
    handleSerial();
}

int updateAudio() { return updateAudioSeq(); }

void setup() {
    Serial.begin(115200);

    setupSequencer();
    setupTones(gCurrentTonesSetup);
    displaySetup();

    startMozzi();
}

void loop() { audioHook(); }
