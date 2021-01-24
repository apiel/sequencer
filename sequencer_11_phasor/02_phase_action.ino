bool gAdsrFreqSetMode = false;

void togglePhase(byte phase, byte pos) {
    int aPhase = gCurrentPattern[pos];
    int powPhase = pow(2, phase);
    if (aPhase & powPhase) {
        gCurrentPattern[pos] -= powPhase;
    } else {
        gCurrentPattern[pos] += powPhase;
    }
}

bool setPhaseFromMidiBtn(byte phaseIdx, byte key) {
    if (key == 40 || key == 16) {
        phases[phaseIdx].setType(mod(phases[phaseIdx].type + 1, 4));
    } else if (key == 17 || key == 41) {
        gAdsrFreqSetMode = !gAdsrFreqSetMode;
    } else if (key == 18 || key == 42) {
        // // we might better use knob for this
        // if (phases[phaseIdx].freqShift > 0) {
        //     phases[phaseIdx].freqShift--;
        // }
    } else if (key == 19 || key == 43) {
        // // we might better use knob for this
        //  if (phases[phaseIdx].freqShift < 16) {
        //     phases[phaseIdx].freqShift++;
        // }
    } else if (key > 31 && key < 40) {
        togglePhase(phaseIdx, key - 32 + 8);
    } else if (key > 7 && key < 16) {
        togglePhase(phaseIdx, key - 8);
    } else {
        return false;
    }
    return true;
}

unsigned int incTime(unsigned int ms, int direction) {
    return between(ms + (direction * (int)gTempo * 0.1), 0, 60000);
}

byte incLevel(byte level, int direction) {
    return between(level + direction, 0, 255);
}

void setPhaseFromMidiKnob(byte phaseIdx, byte optionKey, int direction) {
    Serial.print("setPhaseFromMidi: ");
    Serial.print(phaseIdx);
    Serial.print(" key: ");
    Serial.print(optionKey);
    Serial.print(" dir: ");
    Serial.println(direction);

    Phase<MAX_NUM_CELLS> *phase = &phases[phaseIdx];

    if (optionKey == 2) {
        currentTableId = mod(currentTableId + direction, 20);
        setTable(phaseIdx, currentTableId);
    } else if (optionKey == 5) {
        phase->adsr.setAttackTime(
            incTime(phase->adsr.getTime(ATTACK), direction));
    } else if (optionKey == 6) {
        phase->adsr.setDecayTime(
            incTime(phase->adsr.getTime(DECAY), direction));
    } else if (optionKey == 7) {
        phase->adsr.setSustainTime(
            incTime(phase->adsr.getTime(SUSTAIN), direction));
    } else if (optionKey == 8) {
        phase->adsr.setReleaseTime(
            incTime(phase->adsr.getTime(RELEASE), direction));
    } else if (optionKey == 15) {
        phase->adsr.setAttackLevel(
            incLevel(phase->adsr.getLevel(ATTACK), direction));
    } else if (optionKey == 16) {
        phase->adsr.setDecayLevel(
            incLevel(phase->adsr.getLevel(DECAY), direction));
    } else if (optionKey == 17) {
        phase->adsr.setSustainLevel(
            incLevel(phase->adsr.getLevel(SUSTAIN), direction));
    } else if (optionKey == 18) {
        phase->adsr.setReleaseLevel(
            incLevel(phase->adsr.getLevel(RELEASE), direction));
    }

    // else if (optionKey == 3) {
    //     gPhase[phase].PeakLevel =
    //         between(gPhase[phase].PeakLevel + direction, 0, 250);
    // } else if (optionKey == 4) {
    //     gPhase[phase].SustainLevel =
    //         between(gPhase[phase].SustainLevel + direction, 0, 250);
    // } else if (optionKey == 5) {
    //     gPhase[phase].ATime = between(gPhase[phase].ATime + direction, 0,
    //     100);
    // } else if (optionKey == 6) {
    //     gPhase[phase].DTime = between(gPhase[phase].DTime + direction, 0,
    //     100);
    // } else if (optionKey == 7) {
    //     gPhase[phase].STime = between(gPhase[phase].STime + direction, 0,
    //     100);
    // } else if (optionKey == 8) {
    //     gPhase[phase].RTime = between(gPhase[phase].RTime + direction, 0,
    //     100);
    // } else if (optionKey == 12) {
    //     gPhase[phase].frequency =
    //         between(gPhase[phase].frequency + direction, 0, 2000);
    // } else if (optionKey == 13) {
    //     gPhase[phase].AFreqLevel =
    //         between(gPhase[phase].AFreqLevel + direction, 0, 255);
    // } else if (optionKey == 14) {
    //     gPhase[phase].SFreqLevel =
    //         between(gPhase[phase].SFreqLevel + direction, 0, 255);
    // } else if (optionKey == 15) {
    //     gPhase[phase].RFreqLevel =
    //         between(gPhase[phase].RFreqLevel + direction, 0, 255);
    // } else if (optionKey == 16) {
    //     gPhase[phase].AFreqTime =
    //         between(gPhase[phase].AFreqTime + direction, 0, 100);
    // } else if (optionKey == 17) {
    //     gPhase[phase].SFreqTime =
    //         between(gPhase[phase].SFreqTime + direction, 0, 100);
    // } else if (optionKey == 18) {
    //     gPhase[phase].RFreqTime =
    //         between(gPhase[phase].RFreqTime + direction, 0, 100);
    // }

    // if (optionKey != 2 && optionKey != 12) {
    //     applySetting(phase);
    // }
}

void playPhase() {
    int aPhase = gCurrentPattern[gSeqPhaseIndex];

    for (int i = 0; i < PHASES_COUNT; i++) {
        if (aPhase & (int)pow(2, i)) {
            phases[i].noteOn();
        }
    }
}

void setStepPattern(byte step, int val) { gCurrentPattern[step] = val; }

void assignCurrentPattern(byte index) {
    gCurrentPatternId = index % MAX_PATTERNS;
    for (int i = 0; i < MAX_PHASES; i++) {
        gCurrentPattern[i] = gSeqPhases[gCurrentPatternId][i];
    }
}
