#include <tables/sin2048_int8.h>
#include <tables/triangle2048_int8.h>
#include <tables/whitenoise8192_int8.h>

// new

// #include <ADSR.h>
#include <mozzi_rand.h>
#include <tables/triangle_dist_squared_2048_int8.h>

byte envelopeValue2;

// oscillators
Oscil<TRIANGLE_DIST_SQUARED_2048_NUM_CELLS, AUDIO_RATE> aOscil(
    TRIANGLE_DIST_SQUARED_2048_DATA);  // cool cool

// envelopes
ADSR<CONTROL_RATE, AUDIO_RATE> envelope1;
ADSR<CONTROL_RATE, AUDIO_RATE> envelope2;

int frequency = 45;

byte PeakLevel = 200;
byte SubstainLevel = 150;

// unsigned int ATime = gTempo * 0 / 100;
// unsigned int DTime = gTempo * 0 / 100;
// unsigned int STime = gTempo * 0 / 100;
// unsigned int RTime = gTempo * 100 / 100;

unsigned int ATime = gTempo * 100 / 100;
unsigned int DTime = gTempo * 0 / 100;
unsigned int STime = gTempo * 0 / 100;
unsigned int RTime = gTempo * 0 / 100;

// unsigned int ATime = gTempo * 50 / 100;
// unsigned int DTime = gTempo * 0 / 100;
// unsigned int STime = gTempo * 0 / 100;
// unsigned int RTime = gTempo * 50 / 100;

void setupNotes() {
    envelope1.setLevels(PeakLevel, SubstainLevel, SubstainLevel, 0);
    envelope1.setTimes(ATime, DTime, STime, RTime);

    envelope2.setLevels(200, 200, 200, 0);
    envelope2.setTimes(gTempo * 30 / 100, gTempo * 0 / 100, gTempo * 40 / 100,
                       gTempo * 30 / 100);
}

void playDKick() {
    aOscil.setFreq(frequency);
    envelope1.noteOn();
    // envelope1.noteOff();

    envelope2.noteOn();
}

void updateEnvelopes() {
    envelope1.update();
    envelope2.update();
}

int updateAudioSeq() {
    int freq = frequency + (envelope2.next() >> 1);
    aOscil.setFreq(freq);

    int kickA = (int)(envelope1.next() * aOscil.next()) >> 1;
    int kickSnd = (int)kickA >> 8;

    return kickSnd;
}

byte count = 0;
void playNote() {
    if (count < 50) {
        Serial.print("count: ");
        Serial.println(count);
        count++;
        byte aNote = gSeqNotes[gSeqNoteIndex];
        // 01 - kick
        if (aNote & D_KICK) {
            Serial.println("play kick");
            playDKick();
        }
    }
}
