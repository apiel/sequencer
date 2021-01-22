/*
think about using math cos sin tan to create table

Look at PDResonant it seem awesome :p
Look at synth in general
*/

#include <Oscil.h>  // oscillator template
#include <tables/brownnoise8192_int8.h>
#include <tables/chum78_int8.h>
#include <tables/cos256_int8.h>
#include <tables/noise_static_1_16384_int8.h>
#include <tables/phasor256_int8.h>
#include <tables/pinknoise8192_int8.h>
#include <tables/saw512_int8.h>
#include <tables/saw_analogue512_int8.h>
#include <tables/sin2048_int8.h>
#include <tables/smoothsquare8192_int8.h>
#include <tables/square_analogue512_int8.h>
#include <tables/square_no_alias_2048_int8.h>
#include <tables/triangle1024_int8.h>
#include <tables/triangle2048_int8.h>
#include <tables/triangle_dist_cubed_2048_int8.h>
#include <tables/triangle_dist_squared_2048_int8.h>
#include <tables/triangle_hermes_2048_int8.h>
#include <tables/triangle_valve_2048_int8.h>
#include <tables/triangle_valve_2_2048_int8.h>
#include <tables/waveshape1_softclip_int8.h>
#include <tables/waveshape_chebyshev_3rd_256_int8.h>
#include <tables/waveshape_sigmoid_int8.h>
#include <tables/waveshape_tanh_int8.h>
#include <tables/whitenoise8192_int8.h>

// #include <ADSR.h>
#include "ADSR_FIX.h"

#define DRUM_LEVEL_B 200

#define D_KICK 1
#define D_SNARE 2
#define D_HIHAT 4
#define D_CLAP 8
#define D_CRASH 16
#define D_TOMHI 32

#define MAX_NUM_CELLS 8192

byte currentTableId = 0;

byte gSeqNotes[MAX_PATTERNS][MAX_NOTES] = {
    {D_KICK, 0, D_HIHAT, 0, D_SNARE, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0,
     D_SNARE, 0, D_HIHAT, D_KICK},
    {D_KICK + D_CRASH, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT,
     0, D_CLAP, 0, D_HIHAT, D_KICK},
    {D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0}};

byte gCurrentPattern[MAX_NOTES] = {0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0};

typedef struct Drum {
    const char* name;
    bool useFreqEnvelope;
    ADSR<CONTROL_RATE, AUDIO_RATE> envelope;
    ADSR<CONTROL_RATE, AUDIO_RATE> envelopeFreq;
    Oscil<MAX_NUM_CELLS, AUDIO_RATE> oscil;
    int8_t oscilTable[MAX_NUM_CELLS];
    unsigned int frequency;

    // ADSR
    byte ATime;
    byte DTime;
    byte STime;
    byte RTime;
    byte PeakLevel;
    byte SustainLevel;

    // Frequency envelope
    byte AFreqTime;
    byte SFreqTime;
    byte RFreqTime;
    byte AFreqLevel;
    byte SFreqLevel;
    byte RFreqLevel;
    byte freqShift;
};

Drum gDrum[NOTES_COUNT];

void displayNote() {
    display.clearDisplay();
    display.setCursor(0, 0);
    dprintln("Note %c", getCurrentNoteChar());
    byte note = getCurrentNote();
    dprintln("A %d", gDrum[note].ATime);
    dprintln("D %d", gDrum[note].DTime);
    dprintln("S %d", gDrum[note].STime);
    dprintln("R %d", gDrum[note].RTime);
    dprintln("P %d", gDrum[note].PeakLevel);
    dprintln("S %d", gDrum[note].SustainLevel);

    if (gDrum[note].useFreqEnvelope) {
        dprintxy(6, 1, "A %d", gDrum[note].AFreqTime);
        dprintxy(6, 2, "S %d", gDrum[note].SFreqTime);
        dprintxy(6, 3, "R %d", gDrum[note].RFreqTime);
        dprintxy(6, 4, "A %d", gDrum[note].AFreqLevel);
        dprintxy(6, 5, "S %d", gDrum[note].RFreqLevel);
        dprintxy(6, 6, "R %d", gDrum[note].RFreqLevel);
    }

    dprintxy(12, 1, "%s", gDrum[note].name);
    displayNotePattern(note);
}

void displayNotePattern(byte note) {
    for (byte i = 0; i < MAX_NOTES; i++) {
        int aNote = gCurrentPattern[i];
        if (aNote & (int)pow(2, note)) {
            display.fillRect(i * 8, 57, 6, 6, WHITE);
        } else {
            display.drawRect(i * 8, 57, 6, 6, WHITE);
        }
        if (i == gSeqNoteIndex) {
            display.drawLine(i * 8 + 1, 63, i * 8 + 4, 63, WHITE);
        }
    }
}

void setNoteFromMidiBtn(byte note, byte optionKey) {
    if (optionKey == 0) {
        gDrum[note].useFreqEnvelope = !gDrum[note].useFreqEnvelope;
    } else if (optionKey == 1) {
        if (gDrum[note].freqShift > 0) {
            gDrum[note].freqShift--;
        }
    } else if (optionKey == 2) {
        if (gDrum[note].freqShift < 16) {
            gDrum[note].freqShift++;
        }
    }
}

void setNoteFromMidiKnob(byte note, byte optionKey, int direction) {
    Serial.print("setNoteFromMidi: ");
    Serial.print(note);
    Serial.print(" key: ");
    Serial.print(optionKey);
    Serial.print(" dir: ");
    Serial.println(direction);

    if (optionKey == 2) {
        currentTableId = mod(currentTableId + direction, 24);
        setNoteOptionTable(note, currentTableId);
    } else if (optionKey == 3) {
        gDrum[note].PeakLevel =
            between(gDrum[note].PeakLevel + direction, 0, 250);
    } else if (optionKey == 4) {
        gDrum[note].SustainLevel =
            between(gDrum[note].SustainLevel + direction, 0, 250);
    } else if (optionKey == 5) {
        gDrum[note].ATime = between(gDrum[note].ATime + direction, 0, 100);
    } else if (optionKey == 6) {
        gDrum[note].DTime = between(gDrum[note].DTime + direction, 0, 100);
    } else if (optionKey == 7) {
        gDrum[note].STime = between(gDrum[note].STime + direction, 0, 100);
    } else if (optionKey == 8) {
        gDrum[note].RTime = between(gDrum[note].RTime + direction, 0, 100);
    } else if (optionKey == 12) {
        gDrum[note].frequency =
            between(gDrum[note].frequency + direction, 0, 2000);
    } else if (optionKey == 13) {
        gDrum[note].AFreqLevel =
            between(gDrum[note].AFreqLevel + direction, 0, 255);
    } else if (optionKey == 14) {
        gDrum[note].SFreqLevel =
            between(gDrum[note].SFreqLevel + direction, 0, 255);
    } else if (optionKey == 15) {
        gDrum[note].RFreqLevel =
            between(gDrum[note].RFreqLevel + direction, 0, 255);
    } else if (optionKey == 16) {
        gDrum[note].AFreqTime =
            between(gDrum[note].AFreqTime + direction, 0, 100);
    } else if (optionKey == 17) {
        gDrum[note].SFreqTime =
            between(gDrum[note].SFreqTime + direction, 0, 100);
    } else if (optionKey == 18) {
        gDrum[note].RFreqTime =
            between(gDrum[note].RFreqTime + direction, 0, 100);
    }

    if (optionKey != 2 && optionKey != 12) {
        applySetting(note);
    }
}

void playNote() {
    int aNote = gCurrentPattern[gSeqNoteIndex];

    for (int i = 0; i < NOTES_COUNT; i++) {
        if (aNote & (int)pow(2, i)) {
            if (gDrum[i].useFreqEnvelope) {
                playDoubleEnvNote(&gDrum[i]);
            } else {
                playSimpleEnvNote(&gDrum[i]);
            }
        }
    }
}

void playSimpleEnvNote(struct Drum* ptrDrum) {
    ptrDrum->oscil.setFreq((int)ptrDrum->frequency);
    ptrDrum->envelope.noteOn();
}

void playDoubleEnvNote(struct Drum* ptrDrum) {
    ptrDrum->oscil.setFreq((int)ptrDrum->frequency);
    ptrDrum->envelope.noteOn();
    ptrDrum->envelopeFreq.noteOn();
}

void setStepPattern(byte step, int val) { gCurrentPattern[step] = val; }

void assignCurrentPattern(byte note) {
    for (int i = 0; i < MAX_NOTES; i++) {
        gCurrentPattern[i] = gSeqNotes[note][i];
    }
}

void assignTable(byte note, const char* name, const int8_t* table,
                 int num_cells) {
    byte multi = MAX_NUM_CELLS / num_cells;
    for (int i = 0; i < num_cells; i++) {
        for (int x = 0; x < multi; x++) {
            gDrum[note].oscilTable[i * multi + x] = table[i];
        }
    }
    gDrum[note].oscil.setTable(gDrum[note].oscilTable);
    gDrum[note].name = name;
}

void setupNote(byte note, byte tableId, bool useFreqEnvelope, int frequency) {
    setNoteOptionTable(note, tableId);
    gDrum[note].useFreqEnvelope = useFreqEnvelope;
    gDrum[note].frequency = frequency;

    gDrum[note].ATime = 0;
    gDrum[note].DTime = 0;
    gDrum[note].STime = 0;
    gDrum[note].RTime = 100;
    gDrum[note].PeakLevel = 250;
    gDrum[note].SustainLevel = 200;

    gDrum[note].AFreqTime = 0;
    gDrum[note].SFreqTime = 0;
    gDrum[note].RFreqTime = 100;
    gDrum[note].AFreqLevel = 200;
    gDrum[note].SFreqLevel = 200;
    gDrum[note].RFreqLevel = 0;
    gDrum[note].freqShift = 1;

    applySetting(note);
}

void applySetting(byte note) {
    gDrum[note].envelope.setLevels(gDrum[note].PeakLevel,
                                   gDrum[note].SustainLevel,
                                   gDrum[note].SustainLevel, 0);
    gDrum[note].envelope.setTimes(
        gTempo / 100 * gDrum[note].ATime, gTempo / 100 * gDrum[note].DTime,
        gTempo / 100 * gDrum[note].STime, gTempo / 100 * gDrum[note].RTime);

    gDrum[note].envelopeFreq.setLevels(
        gDrum[note].AFreqLevel, gDrum[note].AFreqLevel, gDrum[note].SFreqLevel,
        gDrum[note].RFreqLevel);
    gDrum[note].envelopeFreq.setTimes(gTempo / 100 * gDrum[note].AFreqTime, 0,
                                      gTempo / 100 * gDrum[note].SFreqTime,
                                      gTempo / 100 * gDrum[note].RFreqTime);
}

void setupNotes() {
    assignCurrentPattern(0);
    // assignCurrentPattern(2);

    setupNote(0, 24, true, 45);
    setupNote(1, 24, true, 150);
    setupNote(2, 12, false, 100);
    setupNote(3, 12, false, 0);
    setupNote(4, 12, false, 0);
    setupNote(5, 2, true, 100);
}

void updateEnvelopes() {
    for (int i = 0; i < NOTES_COUNT; i++) {
        if (gDrum[i].useFreqEnvelope) {
            gDrum[i].envelopeFreq.update();
        }
        gDrum[i].envelope.update();
    }
}

int updateAudioSeq() {
    int ret = 0;
    for (int i = 0; i < NOTES_COUNT; i++) {
        if (gDrum[i].useFreqEnvelope) {
            int freq = gDrum[i].frequency +
                       (gDrum[i].envelopeFreq.next() >> gDrum[i].freqShift);
            gDrum[i].oscil.setFreq(freq);
        }
        ret += (int)((gDrum[i].envelope.next() * gDrum[i].oscil.next()) >> 1);
    }

    // return ret >> 8;
    return (int)(ret * gVolume / MAX_VOLUME) >> 8;
}

void setNoteOptionTable(byte note, byte tableId) {
    if (tableId == 1) {
        assignTable(note, "phasor", PHASOR256_DATA, PHASOR256_NUM_CELLS);
    } else if (tableId == 2) {
        assignTable(note, "tri2048", TRIANGLE2048_DATA, TRIANGLE2048_NUM_CELLS);
    } else if (tableId == 3) {
        assignTable(note, "tri1024", TRIANGLE1024_DATA, TRIANGLE1024_NUM_CELLS);
    } else if (tableId == 4) {
        assignTable(note, "triHermes", TRIANGLE_HERMES_2048_DATA,
                    TRIANGLE_HERMES_2048_NUM_CELLS);
    } else if (tableId == 5) {
        assignTable(note, "triCubeb", TRIANGLE_DIST_CUBED_2048_DATA,
                    TRIANGLE_DIST_CUBED_2048_NUM_CELLS);
    } else if (tableId == 6) {
        assignTable(note, "triSquar", TRIANGLE_DIST_SQUARED_2048_DATA,
                    TRIANGLE_DIST_SQUARED_2048_NUM_CELLS);
    } else if (tableId == 7) {
        assignTable(note, "triValve", TRIANGLE_VALVE_2048_DATA,
                    TRIANGLE_VALVE_2048_NUM_CELLS);
    } else if (tableId == 8) {
        assignTable(note, "triValve2", TRIANGLE_VALVE_2_2048_DATA,
                    TRIANGLE_VALVE_2_2048_NUM_CELLS);
    } else if (tableId == 9) {
        assignTable(note, "cos", COS256_DATA, COS256_NUM_CELLS);
    } else if (tableId == 10) {
        assignTable(note, "analogSquar", SQUARE_ANALOGUE512_DATA,
                    SQUARE_ANALOGUE512_NUM_CELLS);
    } else if (tableId == 11) {
        assignTable(note, "noise_s", NOISE_STATIC_1_16384_DATA,
                    NOISE_STATIC_1_16384_NUM_CELLS);
    } else if (tableId == 12) {
        assignTable(note, "noise_w", WHITENOISE8192_DATA,
                    WHITENOISE8192_NUM_CELLS);
    } else if (tableId == 13) {
        assignTable(note, "noise_p", PINKNOISE8192_DATA,
                    PINKNOISE8192_NUM_CELLS);
    } else if (tableId == 14) {
        assignTable(note, "noise_b", BROWNNOISE8192_DATA,
                    BROWNNOISE8192_NUM_CELLS);
    } else if (tableId == 15) {
        assignTable(note, "saw", SAW512_DATA, SAW512_NUM_CELLS);
    } else if (tableId == 16) {
        assignTable(note, "sawAnalog", SAW_ANALOGUE512_DATA,
                    SAW_ANALOGUE512_NUM_CELLS);
    } else if (tableId == 17) {
        assignTable(note, "chum", CHUM78_DATA, CHUM78_NUM_CELLS);
    } else if (tableId == 18) {
        assignTable(note, "smoothSquar", SMOOTHSQUARE8192_DATA,
                    SMOOTHSQUARE8192_NUM_CELLS);
    } else if (tableId == 19) {
        assignTable(note, "chebyshev", CHEBYSHEV_3RD_256_DATA,
                    CHEBYSHEV_3RD_256_NUM_CELLS);
    } else if (tableId == 20) {
        assignTable(note, "waveSoft", WAVESHAPE1_SOFTCLIP_DATA,
                    WAVESHAPE1_SOFTCLIP_NUM_CELLS);
    } else if (tableId == 21) {
        assignTable(note, "waveSig", WAVESHAPE_SIGMOID_DATA,
                    WAVESHAPE_SIGMOID_NUM_CELLS);
    } else if (tableId == 22) {
        assignTable(note, "waveTanH", WAVESHAPE_TANH_DATA,
                    WAVESHAPE_TANH_NUM_CELLS);
    } else if (tableId == 23) {
        assignTable(note, "noAlias", SQUARE_NO_ALIAS_2048_DATA,
                    SQUARE_NO_ALIAS_2048_NUM_CELLS);
    } else {
        assignTable(note, "sin", SIN2048_DATA, SIN2048_NUM_CELLS);
    }
}
