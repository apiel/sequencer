
#include <ADSR.h>
#include <MozziGuts.h>
#include <Oscil.h>  // oscillator template

// this should be after MozziGuts
#include <EventDelay.h>

#define MAX_NOTES 16  // max # of notes in sequence
#define D_KICK 1

byte gSeqNotes[MAX_NOTES] = {D_KICK, 0, 0, 0, D_KICK, 0, 0, 0,
                             D_KICK, 0, 0, 0, D_KICK, 0, 0, 0};

byte gSeqNoteIndex = 0;
byte gSeqBPM = 120;
unsigned int gTempo = 1000 / ((gSeqBPM * 4) / 60);

// #define YO
#ifdef YO
unsigned long gSeqTimeCurrent = millis();
unsigned long gSeqTimeLast = gSeqTimeCurrent;

void updateControl() {
    gSeqTimeCurrent = millis();
    if (gSeqTimeCurrent - gSeqTimeLast >= gTempo) {
        gSeqNoteIndex = (gSeqNoteIndex + 1) % MAX_NOTES;
        playNote();
        gSeqTimeLast = gSeqTimeLast + gTempo;
    }
    updateEnvelopes();
}
#else
EventDelay noteDelay;
void updateControl() {
    if (noteDelay.ready()) {
        gSeqNoteIndex = (gSeqNoteIndex + 1) % MAX_NOTES;
        playNote();
        noteDelay.start(gTempo);
    }
    updateEnvelopes();
}
#endif

int updateAudio() { return updateAudioSeq(); }
void loop() { audioHook(); }

void setup() {
    Serial.begin(115200);
    Serial.print("Tempo: ");
    Serial.println(gTempo);
    setupNotes();
    startMozzi();
}
