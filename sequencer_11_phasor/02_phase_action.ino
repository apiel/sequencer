
void togglePhase(byte phase, byte pos) {
    int aPhase = gCurrentPattern[pos];
    int powPhase = pow(2, phase);
    if (aPhase & powPhase) {
        gCurrentPattern[pos] -= powPhase;
    } else {
        gCurrentPattern[pos] += powPhase;
    }
}

void setPhaseFromMidiBtn(byte phase, byte optionKey) {
    if (optionKey == 0) {
        // ToDo change phase type
        // gPhase[phase].useFreqEnvelope = !gPhase[phase].useFreqEnvelope;
    } else if (optionKey == 1) {
        if (phases[phase].freqShift > 0) {
            phases[phase].freqShift--;
        }
    } else if (optionKey == 2) {
        if (phases[phase].freqShift < 16) {
            phases[phase].freqShift++;
        }
    }
}

unsigned int incTime(unsigned int ms, int direction) {
    return between(ms + (direction * (int)gTempo * 0.1), 0, 60000);
}

void setPhaseFromMidiKnob(byte phaseIdx, byte optionKey, int direction) {
    Serial.print("setPhaseFromMidi: ");
    Serial.print(phaseIdx);
    Serial.print(" key: ");
    Serial.print(optionKey);
    Serial.print(" dir: ");
    Serial.println(direction);

    Phase<MAX_NUM_CELLS> *phase = &phases[phaseIdx];

    // ToDo...
    // here we have to set gPhase[phase].adsr.setAttack...

    if (optionKey == 2) {
        currentTableId = mod(currentTableId + direction, 20);
        setTable(phaseIdx, currentTableId);
        // } else if (optionKey == 5) {
        //     phase->adsr.getTime(ATTACK) + direction;
        //     phase.adsr.ATime = between(gPhase[phase].ATime + direction, 0,
        //     100);
        // } else if (optionKey == 6) {
        //     gPhase[phase].DTime = between(gPhase[phase].DTime + direction, 0,
        //     100);
        // } else if (optionKey == 7) {
        //     gPhase[phase].STime = between(gPhase[phase].STime + direction, 0,
        //     100);
    } else if (optionKey == 8) {
        phase->adsr.setReleaseTime(
            incTime(phase->adsr.getTime(RELEASE), direction));
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
