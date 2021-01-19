#include <tables/sin2048_int8.h>
#include <tables/triangle2048_int8.h>
#include <tables/whitenoise8192_int8.h>

// new

#include <ADSR.h>
#include <mozzi_rand.h>
#include <tables/triangle_dist_squared_2048_int8.h>

int frequency = 45;  // (setting)
unsigned int ATime = gTempo * 0 / 100;
unsigned int DTime = gTempo * 0 / 100;
unsigned int STime = gTempo * 0 / 100;
unsigned int RTime = gTempo * 100 / 100;

byte PeakLevel = 200;
byte SubstainLevel = 150;

byte envelopeValue2;

// oscillators
Oscil<TRIANGLE_DIST_SQUARED_2048_NUM_CELLS, AUDIO_RATE> aOscil(
    TRIANGLE_DIST_SQUARED_2048_DATA);  // cool cool

// envelopes
ADSR<CONTROL_RATE, AUDIO_RATE> envelope1;
ADSR<CONTROL_RATE, AUDIO_RATE> envelope2;

void setupNotes() {
    envelope1.setLevels(PeakLevel, SubstainLevel, SubstainLevel, 0);
    envelope1.setTimes(ATime, DTime, STime, RTime);

    envelope2.setLevels(PeakLevel, SubstainLevel, SubstainLevel, 0);
    envelope2.setTimes(gTempo * 10 / 100, gTempo * 10 / 100, gTempo * 10 / 100,
                       gTempo * 70 / 100);
}

void playDKick() {
    aOscil.setFreq(frequency);
    envelope1.noteOn();
    envelope2.noteOn();

    envelope1.noteOff();
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
