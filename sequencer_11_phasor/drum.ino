/*
Make the frequency envelope table independent from the main envelope
So the frequency envelope doesnt have to be the same...

when pressing loop the pattern button become synth

Look at PDResonant it seem awesome :p
Look at synth in general:
- FMsynth
- WaveShaper?
*/

// #include <AudioDelay.h>
#include <LowPassFilter.h>
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

#define D_KICK 1
#define D_SNARE 2
#define D_HIHAT 4
#define D_CLAP 8
#define D_CRASH 16
#define D_TOMHI 32

#define MAX_NUM_CELLS 8192

// AudioDelay<256> audioDelay;
// byte gDelayValue = 255;

// seem to be kind of useless
LowPassFilter lpf;
byte gCutoff = 255;
byte gResonance = 0;

byte currentTableId = 0;

byte gSeqDrums[MAX_PATTERNS][MAX_DRUMS] = {
    {D_KICK, 0, D_HIHAT, 0, D_SNARE, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0,
     D_SNARE, 0, D_HIHAT, D_KICK},
    {D_KICK + D_CRASH, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT, 0, D_KICK, 0, D_HIHAT,
     0, D_CLAP, 0, D_HIHAT, D_KICK},
    {D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0, D_KICK, 0, 0, 0}};

byte gCurrentPattern[MAX_DRUMS] = {0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0};

byte gCurrentPatternId = 0;

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

Drum gDrum[DRUMS_COUNT];

void displayDrum() {
    display.clearDisplay();
    display.setCursor(0, 0);
    dprintln("Drum %c", getCurrentDrumChar());
    byte drum = getCurrentDrum();
    dprintln("A %d", gDrum[drum].ATime);
    dprintln("D %d", gDrum[drum].DTime);
    dprintln("S %d", gDrum[drum].STime);
    dprintln("R %d", gDrum[drum].RTime);
    dprintln("P %d", gDrum[drum].PeakLevel);
    dprintln("S %d", gDrum[drum].SustainLevel);

    if (gDrum[drum].useFreqEnvelope) {
        dprintxy(6, 1, "A %d", gDrum[drum].AFreqTime);
        dprintxy(6, 2, "S %d", gDrum[drum].SFreqTime);
        dprintxy(6, 3, "R %d", gDrum[drum].RFreqTime);
        dprintxy(6, 4, "A %d", gDrum[drum].AFreqLevel);
        dprintxy(6, 5, "S %d", gDrum[drum].RFreqLevel);
        dprintxy(6, 6, "R %d", gDrum[drum].RFreqLevel);
        dprintxy(12, 3, "Shift %d", gDrum[drum].freqShift);
    }

    dprintxy(12, 1, "%s", gDrum[drum].name);
    dprintxy(12, 2, "Freq %d", gDrum[drum].frequency);
    displayDrumPattern(drum);
}

void toggleDrum(byte drum, byte pos) {
    int aDrum = gCurrentPattern[pos];
    int powDrum = pow(2, drum);
    if (aDrum & powDrum) {
        gCurrentPattern[pos] -= powDrum;
    } else {
        gCurrentPattern[pos] += powDrum;
    }
}

void displayDrumPattern(byte drum) {
    for (byte i = 0, s = 0; i < MAX_DRUMS; i++) {
        if (i % 4 == 0) s += 3;
        int aDrum = gCurrentPattern[i];
        if (aDrum & (int)pow(2, drum)) {
            display.fillRect(i * 7 + s, 57, 6, 6, WHITE);
        } else {
            display.drawRect(i * 7 + s, 57, 6, 6, WHITE);
        }
        if (i == gSeqDrumIndex) {
            display.drawLine(i * 7 + 1 + s, 63, i * 7 + 4 + s, 63, WHITE);
        }
    }
}

void setDrumFromMidiBtn(byte drum, byte optionKey) {
    if (optionKey == 0) {
        gDrum[drum].useFreqEnvelope = !gDrum[drum].useFreqEnvelope;
    } else if (optionKey == 1) {
        if (gDrum[drum].freqShift > 0) {
            gDrum[drum].freqShift--;
        }
    } else if (optionKey == 2) {
        if (gDrum[drum].freqShift < 16) {
            gDrum[drum].freqShift++;
        }
    }
}

void setDrumFromMidiKnob(byte drum, byte optionKey, int direction) {
    Serial.print("setDrumFromMidi: ");
    Serial.print(drum);
    Serial.print(" key: ");
    Serial.print(optionKey);
    Serial.print(" dir: ");
    Serial.println(direction);

    if (optionKey == 2) {
        currentTableId = mod(currentTableId + direction, 24);
        setDrumOptionTable(drum, currentTableId);
    } else if (optionKey == 3) {
        gDrum[drum].PeakLevel =
            between(gDrum[drum].PeakLevel + direction, 0, 250);
    } else if (optionKey == 4) {
        gDrum[drum].SustainLevel =
            between(gDrum[drum].SustainLevel + direction, 0, 250);
    } else if (optionKey == 5) {
        gDrum[drum].ATime = between(gDrum[drum].ATime + direction, 0, 100);
    } else if (optionKey == 6) {
        gDrum[drum].DTime = between(gDrum[drum].DTime + direction, 0, 100);
    } else if (optionKey == 7) {
        gDrum[drum].STime = between(gDrum[drum].STime + direction, 0, 100);
    } else if (optionKey == 8) {
        gDrum[drum].RTime = between(gDrum[drum].RTime + direction, 0, 100);
    } else if (optionKey == 12) {
        gDrum[drum].frequency =
            between(gDrum[drum].frequency + direction, 0, 2000);
    } else if (optionKey == 13) {
        gDrum[drum].AFreqLevel =
            between(gDrum[drum].AFreqLevel + direction, 0, 255);
    } else if (optionKey == 14) {
        gDrum[drum].SFreqLevel =
            between(gDrum[drum].SFreqLevel + direction, 0, 255);
    } else if (optionKey == 15) {
        gDrum[drum].RFreqLevel =
            between(gDrum[drum].RFreqLevel + direction, 0, 255);
    } else if (optionKey == 16) {
        gDrum[drum].AFreqTime =
            between(gDrum[drum].AFreqTime + direction, 0, 100);
    } else if (optionKey == 17) {
        gDrum[drum].SFreqTime =
            between(gDrum[drum].SFreqTime + direction, 0, 100);
    } else if (optionKey == 18) {
        gDrum[drum].RFreqTime =
            between(gDrum[drum].RFreqTime + direction, 0, 100);
    }

    if (optionKey != 2 && optionKey != 12) {
        applySetting(drum);
    }
}

void playDrum() {
    int aDrum = gCurrentPattern[gSeqDrumIndex];

    for (int i = 0; i < DRUMS_COUNT; i++) {
        if (aDrum & (int)pow(2, i)) {
            if (gDrum[i].useFreqEnvelope) {
                playDoubleEnvDrum(&gDrum[i]);
            } else {
                playSimpleEnvDrum(&gDrum[i]);
            }
        }
    }
}

void playSimpleEnvDrum(struct Drum* ptrDrum) {
    ptrDrum->oscil.setFreq((int)ptrDrum->frequency);
    ptrDrum->envelope.noteOn();
}

void playDoubleEnvDrum(struct Drum* ptrDrum) {
    ptrDrum->oscil.setFreq((int)ptrDrum->frequency);
    ptrDrum->envelope.noteOn();
    ptrDrum->envelopeFreq.noteOn();
}

void setStepPattern(byte step, int val) { gCurrentPattern[step] = val; }

void assignCurrentPattern(byte index) {
    gCurrentPatternId = index % MAX_PATTERNS;
    for (int i = 0; i < MAX_DRUMS; i++) {
        gCurrentPattern[i] = gSeqDrums[gCurrentPatternId][i];
    }
}

byte getCurrentPatternId() { return gCurrentPatternId; }

void assignTable(byte drum, const char* name, const int8_t* table,
                 int num_cells) {
    byte multi = MAX_NUM_CELLS / num_cells;
    for (int i = 0; i < num_cells; i++) {
        for (int x = 0; x < multi; x++) {
            gDrum[drum].oscilTable[i * multi + x] = table[i];
        }
    }
    gDrum[drum].oscil.setTable(gDrum[drum].oscilTable);
    gDrum[drum].name = name;
}

void setupDrum(byte drum, byte tableId, bool useFreqEnvelope, int frequency) {
    setDrumOptionTable(drum, tableId);

    lpf.setCutoffFreqAndResonance(gCutoff, gResonance);

    gDrum[drum].useFreqEnvelope = useFreqEnvelope;
    gDrum[drum].frequency = frequency;

    gDrum[drum].ATime = 0;
    gDrum[drum].DTime = 0;
    gDrum[drum].STime = 0;
    gDrum[drum].RTime = 100;
    gDrum[drum].PeakLevel = 250;
    gDrum[drum].SustainLevel = 200;

    gDrum[drum].AFreqTime = 0;
    gDrum[drum].SFreqTime = 0;
    gDrum[drum].RFreqTime = 100;
    gDrum[drum].AFreqLevel = 200;
    gDrum[drum].SFreqLevel = 200;
    gDrum[drum].RFreqLevel = 0;
    gDrum[drum].freqShift = 1;

    applySetting(drum);
}

void applySetting(byte drum) {
    gDrum[drum].envelope.setLevels(gDrum[drum].PeakLevel,
                                   gDrum[drum].SustainLevel,
                                   gDrum[drum].SustainLevel, 0);
    gDrum[drum].envelope.setTimes(
        gTempo / 100 * gDrum[drum].ATime, gTempo / 100 * gDrum[drum].DTime,
        gTempo / 100 * gDrum[drum].STime, gTempo / 100 * gDrum[drum].RTime);

    gDrum[drum].envelopeFreq.setLevels(
        gDrum[drum].AFreqLevel, gDrum[drum].AFreqLevel, gDrum[drum].SFreqLevel,
        gDrum[drum].RFreqLevel);
    gDrum[drum].envelopeFreq.setTimes(gTempo / 100 * gDrum[drum].AFreqTime, 0,
                                      gTempo / 100 * gDrum[drum].SFreqTime,
                                      gTempo / 100 * gDrum[drum].RFreqTime);
}

void setupDrums() {
    assignCurrentPattern(gCurrentPatternId);

    setupDrum(0, 20, true, 45);
    setupDrum(1, 20, true, 150);
    setupDrum(2, 10, false, 100);
    setupDrum(3, 10, false, 0);
    setupDrum(4, 10, false, 0);
    setupDrum(5, 2, true, 100);
}

void updateEnvelopes() {
    for (int i = 0; i < DRUMS_COUNT; i++) {
        if (gDrum[i].useFreqEnvelope) {
            gDrum[i].envelopeFreq.update();
        }
        gDrum[i].envelope.update();
    }
}

int updateAudioSeq() {
    int ret = 0;
    for (int i = 0; i < DRUMS_COUNT; i++) {
        if (gDrum[i].useFreqEnvelope) {
            int freq = gDrum[i].frequency +
                       (gDrum[i].envelopeFreq.next() >> gDrum[i].freqShift);
            gDrum[i].oscil.setFreq(freq);
        }
        ret += (int)((gDrum[i].envelope.next() * gDrum[i].oscil.next()) >> 1);
    }

    // return ret >> 8;
    return lpf.next((int)(ret * gVolume / MAX_VOLUME)) >> 8;
    // return audioDelay.next(lpf.next((int)(ret * gVolume / MAX_VOLUME)),
    // gDelayValue) >> 8; 
    // return (int)(ret * gVolume / MAX_VOLUME) >> 8;
}

void setDrumOptionTable(byte drum, byte tableId) {
    if (tableId == 1) {
        assignTable(drum, "phasor", PHASOR256_DATA, PHASOR256_NUM_CELLS);
    } else if (tableId == 2) {
        assignTable(drum, "tri2048", TRIANGLE2048_DATA, TRIANGLE2048_NUM_CELLS);
    } else if (tableId == 3) {
        assignTable(drum, "triHermes", TRIANGLE_HERMES_2048_DATA,
                    TRIANGLE_HERMES_2048_NUM_CELLS);
    } else if (tableId == 4) {
        assignTable(drum, "triCubeb", TRIANGLE_DIST_CUBED_2048_DATA,
                    TRIANGLE_DIST_CUBED_2048_NUM_CELLS);
    } else if (tableId == 5) {
        assignTable(drum, "triSquare", TRIANGLE_DIST_SQUARED_2048_DATA,
                    TRIANGLE_DIST_SQUARED_2048_NUM_CELLS);
    } else if (tableId == 6) {
        assignTable(drum, "triValve", TRIANGLE_VALVE_2048_DATA,
                    TRIANGLE_VALVE_2048_NUM_CELLS);
    } else if (tableId == 7) {
        assignTable(drum, "triValve2", TRIANGLE_VALVE_2_2048_DATA,
                    TRIANGLE_VALVE_2_2048_NUM_CELLS);
    } else if (tableId == 8) {
        assignTable(drum, "cos", COS256_DATA, COS256_NUM_CELLS);
    } else if (tableId == 9) {
        assignTable(drum, "analogSqu", SQUARE_ANALOGUE512_DATA,
                    SQUARE_ANALOGUE512_NUM_CELLS);
    } else if (tableId == 10) {
        assignTable(drum, "noise_w", WHITENOISE8192_DATA,
                    WHITENOISE8192_NUM_CELLS);
    } else if (tableId == 11) {
        assignTable(drum, "noise_b", BROWNNOISE8192_DATA,
                    BROWNNOISE8192_NUM_CELLS);
    } else if (tableId == 12) {
        assignTable(drum, "noise_p", PINKNOISE8192_DATA,
                    PINKNOISE8192_NUM_CELLS);
    } else if (tableId == 13) {
        assignTable(drum, "saw", SAW512_DATA, SAW512_NUM_CELLS);
    } else if (tableId == 14) {
        assignTable(drum, "sawAnalog", SAW_ANALOGUE512_DATA,
                    SAW_ANALOGUE512_NUM_CELLS);
    } else if (tableId == 15) {
        assignTable(drum, "smoothSqu", SMOOTHSQUARE8192_DATA,
                    SMOOTHSQUARE8192_NUM_CELLS);
    } else if (tableId == 16) {
        assignTable(drum, "chebyshev", CHEBYSHEV_3RD_256_DATA,
                    CHEBYSHEV_3RD_256_NUM_CELLS);
    } else if (tableId == 17) {
        assignTable(drum, "waveSoft", WAVESHAPE1_SOFTCLIP_DATA,
                    WAVESHAPE1_SOFTCLIP_NUM_CELLS);
    } else if (tableId == 18) {
        assignTable(drum, "waveSig", WAVESHAPE_SIGMOID_DATA,
                    WAVESHAPE_SIGMOID_NUM_CELLS);
    } else if (tableId == 19) {
        assignTable(drum, "noAlias", SQUARE_NO_ALIAS_2048_DATA,
                    SQUARE_NO_ALIAS_2048_NUM_CELLS);
    } else {
        assignTable(drum, "sin", SIN2048_DATA, SIN2048_NUM_CELLS);
    }
}

void increaseCutoff(int direction) {
    gCutoff = (byte)between(gCutoff + (direction * 2), 0, 255);
    lpf.setCutoffFreq(gCutoff);
    // Serial.print("Set gCutoff ");
    // Serial.println(gCutoff);
}

void increaseResonance(int direction) {
    gResonance = (byte)between(gResonance + (direction * 2), 0, 255);
    lpf.setResonance(gResonance);
    // Serial.print("Set gResonance ");
    // Serial.println(gResonance);
}

void displayLpf() {
    dprintln("Cutoff: %d", gCutoff);
    dprintln("Resonance: %d", gResonance);
}
