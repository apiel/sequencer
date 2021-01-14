#include <ADSR.h>
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

#define DRUM_LEVEL_B 200

#define MAX_NUM_CELLS 8192
#define SYNTH_COUNT 6

typedef struct MDSynth {
    byte key;
    bool isDoubleEnv;
    ADSR<CONTROL_RATE, AUDIO_RATE> sMEnvA;
    ADSR<CONTROL_RATE, AUDIO_RATE> sMEnvP;
    Oscil<MAX_NUM_CELLS, AUDIO_RATE> sMDOsc;
    int8_t sMDOscTable[MAX_NUM_CELLS];
    // settings
    int sMFrequency;
    unsigned int sMAttackTime;
    unsigned int sMDecayTime;
    unsigned int sMSustainTime;
    unsigned int sMReleaseTime;
    unsigned int sMReleaseTimeP;
    byte sMAttackLevel;
    byte sMDecayLevel;
    byte sMSustainLevel;
    byte sMReleaseLevel;
    //  unsigned int sMFilterFrequency;
    //  Q0n8 sMFilterResonance;
    byte sMEnvSlope;
    // state
    byte sMEnvValueA;
    byte sMEnvValueP;
};

MDSynth gMSynth[SYNTH_COUNT];

// WS controller

void setNoteOption(byte key, byte optionKey, int val) {
    // 0 is for set table
    if (optionKey == 0) {
        setNoteOptionTable(key, (byte)val);
    } else if (optionKey == 1) {
        gMSynth[key].sMEnvSlope = between(val, 0, 8);
    } else if (optionKey == 2) {
        gMSynth[key].sMFrequency = between(val, -2000, 2000);
    } else if (optionKey == 3) {
        gMSynth[key].sMAttackTime = between(val, 0, 2000);
    } else if (optionKey == 4) {
        gMSynth[key].sMDecayTime = between(val, 0, 2000);
    } else if (optionKey == 5) {
        gMSynth[key].sMSustainTime = between(val, 0, 2000);
    } else if (optionKey == 6) {
        gMSynth[key].sMReleaseTime = between(val, 0, 2000);
    } else if (optionKey == 7) {
        gMSynth[key].sMReleaseTimeP = between(val, 0, 2000);
    }
    if (optionKey > 1) {
        applySetting(key);
    }
}
// End ws

void playNote() {
    int aNote = gSeqNotes[gSeqPatternIndex][gSeqNoteIndex];

    for (int i = 0; i < SYNTH_COUNT; i++) {
        if (aNote & (int)pow(2, i)) {
            if (gMSynth[i].isDoubleEnv) {
                playDoubleEnvNote(&gMSynth[i]);
            } else {
                playSimpleEnvNote(&gMSynth[i]);
            }
        }
    }
}

void playSimpleEnvNote(struct MDSynth* ptrSynth) {
    ptrSynth->sMDOsc.setFreq(ptrSynth->sMFrequency);
    ptrSynth->sMEnvA.setReleaseTime(ptrSynth->sMReleaseTime);
    ptrSynth->sMEnvA.noteOn();
    ptrSynth->sMEnvA.noteOff();
}

void playDoubleEnvNote(struct MDSynth* ptrSynth) {
    ptrSynth->sMDOsc.setFreq(ptrSynth->sMFrequency);
    ptrSynth->sMEnvA.setReleaseTime(ptrSynth->sMReleaseTime);
    ptrSynth->sMEnvA.noteOn();
    ptrSynth->sMEnvP.noteOn();
    ptrSynth->sMEnvA.noteOff();
    ptrSynth->sMEnvP.noteOff();
}

void assignTable(byte key, const int8_t* table, int num_cells) {
    byte multi = MAX_NUM_CELLS / num_cells;
    for (int i = 0; i < num_cells; i++) {
        for (int x = 0; x < multi; x++) {
            gMSynth[key].sMDOscTable[i * multi + x] = table[i];
        }
    }
    gMSynth[key].sMDOsc.setTable(gMSynth[key].sMDOscTable);
}

void setupNote(byte key, const int8_t* table, int num_cells, bool isDoubleEnv,
               int frequency, unsigned int releaseTime,
               unsigned int releaseTimeP, byte envSlope) {
    assignTable(key, table, num_cells);
    gMSynth[key].isDoubleEnv = isDoubleEnv;
    gMSynth[key].sMFrequency = frequency;  // (setting)
    gMSynth[key].sMAttackTime = 0;
    gMSynth[key].sMDecayTime = 0;
    gMSynth[key].sMSustainTime = 0;
    gMSynth[key].sMReleaseTime = releaseTime;
    gMSynth[key].sMReleaseTimeP = releaseTimeP;
    gMSynth[key].sMAttackLevel = DRUM_LEVEL_B;
    gMSynth[key].sMDecayLevel = DRUM_LEVEL_B;
    gMSynth[key].sMSustainLevel = DRUM_LEVEL_B;
    gMSynth[key].sMReleaseLevel = 0;
    //  gMSynth[key].sMFilterFrequency = 0;
    //  gMSynth[key].sMFilterResonance = 0;
    gMSynth[key].sMEnvSlope = envSlope;
    applySetting(key);
}

void applySetting(byte key) {
    gMSynth[key].sMEnvA.setLevels(
        gMSynth[key].sMAttackLevel, gMSynth[key].sMDecayLevel,
        gMSynth[key].sMSustainLevel, gMSynth[key].sMReleaseLevel);
    gMSynth[key].sMEnvA.setTimes(
        gMSynth[key].sMAttackTime, gMSynth[key].sMDecayTime,
        gMSynth[key].sMSustainTime, gMSynth[key].sMReleaseTime);
    gMSynth[key].sMEnvP.setLevels(
        gMSynth[key].sMAttackLevel, gMSynth[key].sMDecayLevel,
        gMSynth[key].sMSustainLevel, gMSynth[key].sMReleaseLevel);
    gMSynth[key].sMEnvP.setTimes(
        gMSynth[key].sMAttackTime, gMSynth[key].sMDecayTime,
        gMSynth[key].sMSustainTime, gMSynth[key].sMReleaseTimeP);
}

void setupNotes() {
    setupNote(0, SIN2048_DATA, SIN2048_NUM_CELLS, true, 45, 170, 170, 1);
    setupNote(1, SIN2048_DATA, SIN2048_NUM_CELLS, true, 150, 160, 140, 1);
    setupNote(2, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS, false, 100, 35,
              0, 0);
    setupNote(3, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS, false, 0, 110,
              0, 0);
    setupNote(4, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS, false, 0, 500,
              0, 0);
    setupNote(5, TRIANGLE2048_DATA, TRIANGLE2048_NUM_CELLS, true, 100, 200, 200,
              1);
}

void updateEnvelopes() {
    for (int i = 0; i < SYNTH_COUNT; i++) {
        if (gMSynth[i].isDoubleEnv) {
            gMSynth[i].sMEnvA.update();
            gMSynth[i].sMEnvP.update();
            gMSynth[i].sMDOsc.setFreq(
                gMSynth[i].sMFrequency +
                (gMSynth[i].sMEnvValueP >> gMSynth[i].sMEnvSlope));
        } else {
            gMSynth[i].sMEnvA.update();
        }
    }
}

int updateAudioSeq() {
    int ret = 0;
    for (int i = 0; i < SYNTH_COUNT; i++) {
        gMSynth[i].sMEnvValueA = gMSynth[i].sMEnvA.next();
        gMSynth[i].sMEnvValueP = gMSynth[i].sMEnvP.next();
        ret += (int)((gMSynth[i].sMEnvValueA * gMSynth[i].sMDOsc.next()) >> 1);
    }

    return ret >> 8;
}

void setNoteOptionTable(byte key, byte tableId) {
    if (tableId == 1) {
        assignTable(key, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS);
    } else if (tableId == 2) {
        assignTable(key, TRIANGLE2048_DATA, TRIANGLE2048_NUM_CELLS);
    } else if (tableId == 3) {
        assignTable(key, SQUARE_ANALOGUE512_DATA, SQUARE_ANALOGUE512_NUM_CELLS);
    } else if (tableId == 4) {
        assignTable(key, COS256_DATA, COS256_NUM_CELLS);
    } else if (tableId == 5) {
        assignTable(key, NOISE_STATIC_1_16384_DATA,
                    NOISE_STATIC_1_16384_NUM_CELLS);
    } else if (tableId == 6) {
        assignTable(key, PHASOR256_DATA, PHASOR256_NUM_CELLS);
    } else if (tableId == 7) {
        assignTable(key, PINKNOISE8192_DATA, PINKNOISE8192_NUM_CELLS);
    } else if (tableId == 8) {
        assignTable(key, SAW512_DATA, SAW512_NUM_CELLS);
    } else if (tableId == 9) {
        assignTable(key, BROWNNOISE8192_DATA, BROWNNOISE8192_NUM_CELLS);
    } else if (tableId == 10) {
        assignTable(key, CHUM78_DATA, CHUM78_NUM_CELLS);
    } else if (tableId == 11) {
        assignTable(key, SAW_ANALOGUE512_DATA, SAW_ANALOGUE512_NUM_CELLS);
    } else if (tableId == 12) {
        assignTable(key, SMOOTHSQUARE8192_DATA, SMOOTHSQUARE8192_NUM_CELLS);
    } else if (tableId == 13) {
        assignTable(key, TRIANGLE1024_DATA, TRIANGLE1024_NUM_CELLS);
    } else if (tableId == 14) {
        assignTable(key, TRIANGLE_HERMES_2048_DATA,
                    TRIANGLE_HERMES_2048_NUM_CELLS);
    } else if (tableId == 15) {
        assignTable(key, TRIANGLE_DIST_CUBED_2048_DATA,
                    TRIANGLE_DIST_CUBED_2048_NUM_CELLS);
    } else if (tableId == 16) {
        assignTable(key, TRIANGLE_DIST_SQUARED_2048_DATA,
                    TRIANGLE_DIST_SQUARED_2048_NUM_CELLS);
    } else if (tableId == 17) {
        assignTable(key, TRIANGLE_VALVE_2048_DATA,
                    TRIANGLE_VALVE_2048_NUM_CELLS);
    } else if (tableId == 18) {
        assignTable(key, TRIANGLE_VALVE_2_2048_DATA,
                    TRIANGLE_VALVE_2_2048_NUM_CELLS);
    } else if (tableId == 19) {
        assignTable(key, WAVESHAPE1_SOFTCLIP_DATA,
                    WAVESHAPE1_SOFTCLIP_NUM_CELLS);
    } else if (tableId == 20) {
        assignTable(key, CHEBYSHEV_3RD_256_DATA, CHEBYSHEV_3RD_256_NUM_CELLS);
    } else if (tableId == 21) {
        assignTable(key, WAVESHAPE_SIGMOID_DATA, WAVESHAPE_SIGMOID_NUM_CELLS);
    } else if (tableId == 22) {
        assignTable(key, WAVESHAPE_TANH_DATA, WAVESHAPE_TANH_NUM_CELLS);
    } else if (tableId == 23) {
        assignTable(key, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS);
    } else if (tableId == 24) {
        assignTable(key, SQUARE_NO_ALIAS_2048_DATA,
                    SQUARE_NO_ALIAS_2048_NUM_CELLS);
    } else {
        assignTable(key, SIN2048_DATA, SIN2048_NUM_CELLS);
    }
}
