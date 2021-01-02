#include <MozziGuts.h>
#include <ADSR.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h>
#include <tables/triangle2048_int8.h>
#include <tables/whitenoise8192_int8.h>
#include <ClickButton.h>

#define CONTROL_RATE 128 // Hz, powers of 2 are most reliable

#define MAX_PATTERNS 3
#define MAX_NOTES 16  // max # of notes in sequence
#define D_KICK 1
#define D_SNARE 2
#define D_HIHAT 4
#define D_CLAP 8
#define D_CRASH 16
#define D_TOMHI 32

#define PIN_BTN_1 5 // d1
#define PIN_BTN_2 16 // d0
#define PIN_BTN_3 0 // d3

ClickButton btn3(PIN_BTN_3, LOW, CLICKBTN_PULLUP);

byte gSeqNotes[MAX_PATTERNS][MAX_NOTES] = {
  { D_KICK, 0, D_HIHAT, 0, D_SNARE, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0,
    D_SNARE, 0, D_HIHAT, D_KICK
  },
  { D_KICK + D_CRASH, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT,
    0, D_CLAP, 0, D_HIHAT, D_KICK
  },
  {D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0}
};

int gSelected = 0;
bool gSeqNoteOn = false;
bool gSeqPlay = true;
bool gSyncNoteOn = false;

byte gSeqNoteIndex = 0;
byte gSeqPatternIndex = 0;

typedef struct {
  uint8_t gSeqGatePercent;
  byte gSeqBPM = 120; // tempo, BPM (beats per minute)
  unsigned int gSeqT16 = 125; // length in ms of 1/16
} SeqBase;

SeqBase gSeqBase;

unsigned long gSeqTimeCurrent;
unsigned long gSeqTimeLast;
unsigned long gSeqTimeGate;

void setTempo() {
  gSeqBase.gSeqT16 = 1000 / ((gSeqBase.gSeqBPM * 4) / ((float)60));
}

void calcGate() {
  gSeqTimeGate = (gSeqBase.gSeqT16 * gSeqBase.gSeqGatePercent) / 100;
}

void setSelector() {
  btn3.Update();
  if (btn3.clicks != 0) {
    gSelected = (gSelected + btn3.clicks) % 3;
    if (gSelected == 0) {
      Serial.println("play");
    } else if (gSelected == 1) {
      Serial.println("sel BPM");
    } else if (gSelected == 2) {
      Serial.println("sel sequence gate percentage");
    }
  }
}

void setValue() {
  int btn1 = digitalRead(PIN_BTN_1);
  int btn2 = digitalRead(PIN_BTN_2);

  if (btn1 || btn2) {
    Serial.print("btn: ");
    Serial.print(btn1);
    Serial.print(" - ");
    Serial.println(btn2);
    float val = btn1 ? 1 : -1;

    if (gSelected == 0) {
      //play = true;
      gSeqPlay = btn1 > 0;
      Serial.print("Play: ");
      Serial.println(gSeqPlay);
    } else if (gSelected == 1) {
      if (gSeqBase.gSeqBPM > 10 && gSeqBase.gSeqBPM < 1000) {
        gSeqBase.gSeqBPM = gSeqBase.gSeqBPM + val;
        setTempo();
      }
      Serial.print("set BPM: ");
      Serial.println(gSeqBase.gSeqBPM);
    } else if (gSelected == 2) {
      if (gSeqBase.gSeqGatePercent > 0 && gSeqBase.gSeqGatePercent < 99) {
        gSeqBase.gSeqGatePercent = gSeqBase.gSeqGatePercent + val;
        calcGate();
      }
      Serial.print("set sequence gate percentage: ");
      Serial.println(gSeqBase.gSeqGatePercent);
    }
  }
}

void updateControl() {
  setSelector();
  setValue();

  if (gSeqPlay) {
    gSeqTimeCurrent = millis();
    if ((gSeqTimeCurrent - gSeqTimeLast >= gSeqBase.gSeqT16) && !gSeqNoteOn) {
      // gSyncNoteOn should not be necessary, we could run playNote directly there
      gSyncNoteOn = true;
      gSeqTimeLast = gSeqTimeLast + gSeqBase.gSeqT16;
    } else {
      gSyncNoteOn = false;
    }

    if (gSyncNoteOn) {
      gSeqNoteIndex++;
      if (gSeqNoteIndex >= MAX_NOTES) {
        gSeqNoteIndex = 0;
      }
      playNote();
      // Serial.println("should play note");
      gSyncNoteOn = false;
    }

    if (gSeqTimeCurrent - gSeqTimeLast >= gSeqTimeGate) {
      gSeqNoteOn = false;
    }
    updateEnvelopes();
  }
}

int updateAudio() {
  if (gSeqPlay) {
    return updateAudioSeq();
  }
  return 0;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BTN_1, INPUT);
  pinMode(PIN_BTN_2, INPUT);

  btn3.debounceTime   = 20;   // Debounce timer in ms
  btn3.multiclickTime = 250;  // Time limit for multi clicks
  btn3.longClickTime  = 3000; // time until "held-down clicks" register

  gSeqBase.gSeqBPM = 120; // tempo, BPM (beats per minute)
  gSeqBase.gSeqGatePercent = 50;
  setTempo();
  calcGate();

  gSeqTimeCurrent = millis();
  gSeqTimeLast = gSeqTimeCurrent;

  setupNotes();

  startMozzi(CONTROL_RATE);
}

void loop() {
  audioHook();
}
