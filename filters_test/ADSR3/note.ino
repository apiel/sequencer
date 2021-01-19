#include <tables/sin2048_int8.h>
#include <tables/triangle2048_int8.h>
#include <tables/whitenoise8192_int8.h>

// new

#include <ADSR.h>
#include <mozzi_rand.h>
#include <tables/triangle_dist_squared_2048_int8.h>

int frequency = 45;  // (setting)
unsigned int ATime = 0; //gTempo * 10 / 100;
unsigned int DTime = 0; //gTempo * 10 / 100;
unsigned int STime = 0; //gTempo * 70 / 100;
unsigned int RTime = 100; //gTempo * 10 / 100;

byte ALevel = 200;
byte DLevel = 150;
byte SLevel = 150;
byte RLevel = 0;

byte sMEnvValueA;
byte sMEnvValueP;

// oscillators
Oscil<TRIANGLE_DIST_SQUARED_2048_NUM_CELLS, AUDIO_RATE> aOscil(
    TRIANGLE_DIST_SQUARED_2048_DATA);  // cool cool

// envelopes
ADSR<CONTROL_RATE, AUDIO_RATE> envelope1;
ADSR<CONTROL_RATE, AUDIO_RATE> envelope2;

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

void playDKick() {
    aOscil.setFreq(frequency);
    envelope1.noteOn();
    envelope2.noteOn();

    envelope1.noteOff();
    envelope2.noteOff();
}

void setupNotes() {
    envelope1.setLevels(ALevel, DLevel, SLevel, RLevel);
    envelope1.setTimes(ATime, DTime, STime, RTime);

    envelope2.setLevels(ALevel, DLevel, SLevel, RLevel);
    envelope2.setTimes(ATime, DTime, STime, RTime);
}

void updateEnvelopes() {
    envelope1.update();
    envelope2.update();

    int freq = frequency + (sMEnvValueP >> 1);
    aOscil.setFreq(freq);
}

int updateAudioSeq() {
    sMEnvValueA = envelope1.next();
    sMEnvValueP = envelope2.next();

    int kickA = (int)(sMEnvValueA * aOscil.next()) >> 1;
    int kickSnd = (int)kickA >> 8;

    return kickSnd;
}
