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

typedef struct MDSynth {
    bool isDoubleEnv;
    ADSR<CONTROL_RATE, AUDIO_RATE> sMEnvA;
    ADSR<CONTROL_RATE, AUDIO_RATE> sMEnvP;
    Oscil<MAX_NUM_CELLS, AUDIO_RATE> sMDOsc;
    int8_t sMDOscTable[MAX_NUM_CELLS];
    // settings
    unsigned int sMFrequency;
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

MDSynth gMSynth[NOTES_COUNT];

void setNoteFromMidi(byte note, byte optionKey, int direction) {
    Serial.print("setNoteFromMidi: ");
    Serial.print(note);
    Serial.print(" key: ");
    Serial.print(optionKey);
    Serial.print(" dir: ");
    Serial.println(direction);

    if (optionKey == 0) {
        gMSynth[note].isDoubleEnv = direction == 2;
    } else if (optionKey == 2) {
        currentTableId = mod(currentTableId + direction, 24);
        setNoteOptionTable(note);
    } else if (optionKey == 3) {
        gMSynth[note].sMEnvSlope =
            between(gMSynth[note].sMEnvSlope + direction, 0, 8);
    } else if (optionKey == 4) {
        gMSynth[note].sMFrequency =
            between(gMSynth[note].sMFrequency + direction, 0, 2000);
    } else if (optionKey == 5) {
        gMSynth[note].sMAttackTime =
            between(gMSynth[note].sMAttackTime + direction, 0, 2000);
    } else if (optionKey == 6) {
        gMSynth[note].sMDecayTime =
            between(gMSynth[note].sMDecayTime + direction, 0, 2000);
    } else if (optionKey == 7) {
        gMSynth[note].sMSustainTime =
            between(gMSynth[note].sMSustainTime + direction, 0, 2000);
    } else if (optionKey == 8) {
        gMSynth[note].sMReleaseTime =
            between(gMSynth[note].sMReleaseTime + direction, 0, 2000);
    } else if (optionKey == 12) {
        gMSynth[note].sMReleaseTimeP =
            between(gMSynth[note].sMReleaseTimeP + direction, 0, 2000);
    } else if (optionKey == 13) {
        gMSynth[note].sMAttackLevel =
            between(gMSynth[note].sMAttackLevel + direction, 0, 255);
    } else if (optionKey == 14) {
        gMSynth[note].sMDecayLevel =
            between(gMSynth[note].sMDecayLevel + direction, 0, 255);
    } else if (optionKey == 15) {
        gMSynth[note].sMSustainLevel =
            between(gMSynth[note].sMSustainLevel + direction, 0, 255);
    } else if (optionKey == 16) {
        gMSynth[note].sMReleaseLevel =
            between(gMSynth[note].sMReleaseLevel + direction, 0, 255);
    }
    if (optionKey > 2) {
        applySetting(note);
    }
}

void playNote() {
    int aNote = gCurrentPattern[gSeqNoteIndex];

    for (int i = 0; i < NOTES_COUNT; i++) {
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
    ptrSynth->sMDOsc.setFreq((int)ptrSynth->sMFrequency);
    ptrSynth->sMEnvA.setReleaseTime(ptrSynth->sMReleaseTime);
    ptrSynth->sMEnvA.noteOn();
    ptrSynth->sMEnvA.noteOff();
}

void playDoubleEnvNote(struct MDSynth* ptrSynth) {
    ptrSynth->sMDOsc.setFreq((int)ptrSynth->sMFrequency);
    ptrSynth->sMEnvA.setReleaseTime(ptrSynth->sMReleaseTime);
    ptrSynth->sMEnvA.noteOn();
    ptrSynth->sMEnvP.noteOn();
    ptrSynth->sMEnvA.noteOff();
    ptrSynth->sMEnvP.noteOff();
}

void setStepPattern(byte step, int val) { gCurrentPattern[step] = val; }

void assignCurrentPattern(byte note) {
    for (int i = 0; i < MAX_NOTES; i++) {
        gCurrentPattern[i] = gSeqNotes[note][i];
    }
}

void assignTable(byte note, const int8_t* table, int num_cells) {
    byte multi = MAX_NUM_CELLS / num_cells;
    for (int i = 0; i < num_cells; i++) {
        for (int x = 0; x < multi; x++) {
            gMSynth[note].sMDOscTable[i * multi + x] = table[i];
        }
    }
    gMSynth[note].sMDOsc.setTable(gMSynth[note].sMDOscTable);
}

void setupNote(byte note, const int8_t* table, int num_cells, bool isDoubleEnv,
               int frequency, unsigned int releaseTime,
               unsigned int releaseTimeP, byte envSlope) {
    assignTable(note, table, num_cells);
    gMSynth[note].isDoubleEnv = isDoubleEnv;
    gMSynth[note].sMFrequency = frequency;  // (setting)
    gMSynth[note].sMAttackTime = 0;
    gMSynth[note].sMDecayTime = 0;
    gMSynth[note].sMSustainTime = 0;
    gMSynth[note].sMReleaseTime = releaseTime;
    gMSynth[note].sMReleaseTimeP = releaseTimeP;
    gMSynth[note].sMAttackLevel = DRUM_LEVEL_B;
    gMSynth[note].sMDecayLevel = DRUM_LEVEL_B;
    gMSynth[note].sMSustainLevel = DRUM_LEVEL_B;
    gMSynth[note].sMReleaseLevel = 0;
    //  gMSynth[note].sMFilterFrequency = 0;
    //  gMSynth[note].sMFilterResonance = 0;
    gMSynth[note].sMEnvSlope = envSlope;
    applySetting(note);
}

void applySetting(byte note) {
    gMSynth[note].sMEnvA.setLevels(
        gMSynth[note].sMAttackLevel, gMSynth[note].sMDecayLevel,
        gMSynth[note].sMSustainLevel, gMSynth[note].sMReleaseLevel);
    gMSynth[note].sMEnvA.setTimes(
        gMSynth[note].sMAttackTime, gMSynth[note].sMDecayTime,
        gMSynth[note].sMSustainTime, gMSynth[note].sMReleaseTime);
    gMSynth[note].sMEnvP.setLevels(
        gMSynth[note].sMAttackLevel, gMSynth[note].sMDecayLevel,
        gMSynth[note].sMSustainLevel, gMSynth[note].sMReleaseLevel);
    gMSynth[note].sMEnvP.setTimes(
        gMSynth[note].sMAttackTime, gMSynth[note].sMDecayTime,
        gMSynth[note].sMSustainTime, gMSynth[note].sMReleaseTimeP);
}

void setupNotes() {
    assignCurrentPattern(0);

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
    for (int i = 0; i < NOTES_COUNT; i++) {
        if (gMSynth[i].isDoubleEnv) {
            gMSynth[i].sMEnvA.update();
            gMSynth[i].sMEnvP.update();
            gMSynth[i].sMDOsc.setFreq(
                (int)gMSynth[i].sMFrequency +
                (gMSynth[i].sMEnvValueP >> gMSynth[i].sMEnvSlope));
        } else {
            gMSynth[i].sMEnvA.update();
        }
    }
}

int updateAudioSeq() {
    int ret = 0;
    for (int i = 0; i < NOTES_COUNT; i++) {
        gMSynth[i].sMEnvValueA = gMSynth[i].sMEnvA.next();
        gMSynth[i].sMEnvValueP = gMSynth[i].sMEnvP.next();
        ret += (int)((gMSynth[i].sMEnvValueA * gMSynth[i].sMDOsc.next()) >> 1);
    }

    return ret >> 8;
}

void setNoteOptionTable(byte note) {
    if (currentTableId == 1) {
        assignTable(note, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS);
    } else if (currentTableId == 2) {
        assignTable(note, TRIANGLE2048_DATA, TRIANGLE2048_NUM_CELLS);
    } else if (currentTableId == 3) {
        assignTable(note, SQUARE_ANALOGUE512_DATA,
                    SQUARE_ANALOGUE512_NUM_CELLS);
    } else if (currentTableId == 4) {
        assignTable(note, COS256_DATA, COS256_NUM_CELLS);
    } else if (currentTableId == 5) {
        assignTable(note, NOISE_STATIC_1_16384_DATA,
                    NOISE_STATIC_1_16384_NUM_CELLS);
    } else if (currentTableId == 6) {
        assignTable(note, PHASOR256_DATA, PHASOR256_NUM_CELLS);
    } else if (currentTableId == 7) {
        assignTable(note, PINKNOISE8192_DATA, PINKNOISE8192_NUM_CELLS);
    } else if (currentTableId == 8) {
        assignTable(note, SAW512_DATA, SAW512_NUM_CELLS);
    } else if (currentTableId == 9) {
        assignTable(note, BROWNNOISE8192_DATA, BROWNNOISE8192_NUM_CELLS);
    } else if (currentTableId == 10) {
        assignTable(note, CHUM78_DATA, CHUM78_NUM_CELLS);
    } else if (currentTableId == 11) {
        assignTable(note, SAW_ANALOGUE512_DATA, SAW_ANALOGUE512_NUM_CELLS);
    } else if (currentTableId == 12) {
        assignTable(note, SMOOTHSQUARE8192_DATA, SMOOTHSQUARE8192_NUM_CELLS);
    } else if (currentTableId == 13) {
        assignTable(note, TRIANGLE1024_DATA, TRIANGLE1024_NUM_CELLS);
    } else if (currentTableId == 14) {
        assignTable(note, TRIANGLE_HERMES_2048_DATA,
                    TRIANGLE_HERMES_2048_NUM_CELLS);
    } else if (currentTableId == 15) {
        assignTable(note, TRIANGLE_DIST_CUBED_2048_DATA,
                    TRIANGLE_DIST_CUBED_2048_NUM_CELLS);
    } else if (currentTableId == 16) {
        assignTable(note, TRIANGLE_DIST_SQUARED_2048_DATA,
                    TRIANGLE_DIST_SQUARED_2048_NUM_CELLS);
    } else if (currentTableId == 17) {
        assignTable(note, TRIANGLE_VALVE_2048_DATA,
                    TRIANGLE_VALVE_2048_NUM_CELLS);
    } else if (currentTableId == 18) {
        assignTable(note, TRIANGLE_VALVE_2_2048_DATA,
                    TRIANGLE_VALVE_2_2048_NUM_CELLS);
    } else if (currentTableId == 19) {
        assignTable(note, WAVESHAPE1_SOFTCLIP_DATA,
                    WAVESHAPE1_SOFTCLIP_NUM_CELLS);
    } else if (currentTableId == 20) {
        assignTable(note, CHEBYSHEV_3RD_256_DATA, CHEBYSHEV_3RD_256_NUM_CELLS);
    } else if (currentTableId == 21) {
        assignTable(note, WAVESHAPE_SIGMOID_DATA, WAVESHAPE_SIGMOID_NUM_CELLS);
    } else if (currentTableId == 22) {
        assignTable(note, WAVESHAPE_TANH_DATA, WAVESHAPE_TANH_NUM_CELLS);
    } else if (currentTableId == 23) {
        assignTable(note, WHITENOISE8192_DATA, WHITENOISE8192_NUM_CELLS);
    } else if (currentTableId == 24) {
        assignTable(note, SQUARE_NO_ALIAS_2048_DATA,
                    SQUARE_NO_ALIAS_2048_NUM_CELLS);
    } else {
        assignTable(note, SIN2048_DATA, SIN2048_NUM_CELLS);
    }
}
