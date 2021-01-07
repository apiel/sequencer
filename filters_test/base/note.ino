#define DRUM_LEVEL 150

int sMFrequency = 45;  // (setting)
unsigned int sMAttackTime = 0;
unsigned int sMDecayTime = 0;
unsigned int sMSustainTime = 0;
unsigned int sMReleaseTime = 170;
unsigned int sMReleaseTimeP = 170;
byte sMAttackLevel = DRUM_LEVEL;
byte sMDecayLevel = DRUM_LEVEL;
byte sMSustainLevel = DRUM_LEVEL;
byte sMReleaseLevel = 0;
byte sMFilterFrequency = 0;
byte sMFilterResonance = 0;
byte sMEnvSlope = 1;
byte sMEnvValueA;
byte sMEnvValueP;

// oscillators
Oscil<SIN2048_NUM_CELLS, AUDIO_RATE> gMDOscKick(SIN2048_DATA);

// envelopes
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvKickA;
ADSR<CONTROL_RATE, AUDIO_RATE> gMEnvKickP;

void playNote() {
    byte aNote = gSeqNotes[gSeqNoteIndex];

    // 01 - kick
    if (aNote & D_KICK) {
        playDKick();
    }
}

void playDKick() {
    gMDOscKick.setFreq(sMFrequency);
    gMEnvKickA.noteOn();
    gMEnvKickP.noteOn();
    gMEnvKickA.noteOff();
    gMEnvKickP.noteOff();
}

void setupNotes() {
    gMEnvKickA.setLevels(sMAttackLevel, sMDecayLevel, sMSustainLevel,
                         sMReleaseLevel);
    gMEnvKickA.setTimes(sMAttackTime, sMDecayTime, sMSustainTime,
                        sMReleaseTime);
    gMEnvKickP.setLevels(sMAttackLevel, sMDecayLevel, sMSustainLevel,
                         sMReleaseLevel);
    gMEnvKickP.setTimes(sMAttackTime, sMDecayTime, sMSustainTime,
                        sMReleaseTimeP);
}

void updateEnvelopes() {
    gMEnvKickA.update();
    gMEnvKickP.update();
    gMDOscKick.setFreq(sMFrequency + (sMEnvValueP >> sMEnvSlope));  // (setting)
}

int updateAudioSeq() {
    sMEnvValueA = gMEnvKickA.next();
    sMEnvValueP = gMEnvKickP.next();

    return (int)((sMEnvValueA * gMDOscKick.next()) >> 1) >> 8;
}
