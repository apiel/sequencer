
#include <MozziGuts.h>
#include <ADSR.h>
#include <Oscil.h>
#include <tables/triangle_dist_squared_2048_int8.h>

// this should be after MozziGuts
#include <EventDelay.h>

byte gSeqBPM = 80;
unsigned int gTempo = 1000 / ((gSeqBPM * 4) / 60);
byte delayBetweenNote = 3 * gTempo;

byte envelopeValue2;

// oscillators
Oscil<TRIANGLE_DIST_SQUARED_2048_NUM_CELLS, AUDIO_RATE> aOscil(
    TRIANGLE_DIST_SQUARED_2048_DATA);

// envelopes
ADSR<CONTROL_RATE, AUDIO_RATE> envelope1;
ADSR<CONTROL_RATE, AUDIO_RATE> envelope2;

int frequency = 45;

EventDelay noteDelay;
void updateControl() {
    if (noteDelay.ready()) {
        aOscil.setFreq(frequency);
        envelope1.noteOn();
        envelope2.noteOn();
        noteDelay.start(gTempo + delayBetweenNote);
    }
    envelope1.update();
    envelope2.update();
}

int updateAudio() {
    int freq = frequency + (envelope2.next() >> 1);
    aOscil.setFreq(freq);
    return (int)((envelope1.next() * aOscil.next()) >> 1) >> 8;
}

void loop() { audioHook(); }

byte PeakLevel = 200;
byte SubstainLevel = 150;
void setup() {
    envelope1.setLevels(PeakLevel, SubstainLevel, SubstainLevel, 0);
    envelope1.setTimes(gTempo * 0 / 100, gTempo * 0 / 100, gTempo * 0 / 100,
                       gTempo * 100 / 100);

    envelope2.setLevels(200, 200, 200, 0);
    envelope2.setTimes(gTempo * 30 / 100, gTempo * 0 / 100, gTempo * 40 / 100,
                       gTempo * 30 / 100);

    startMozzi();
}
