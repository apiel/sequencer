bool gMcMode = false;
byte gStepMode = 0;

void togglePhase(byte phaseIdx, byte pos) {
    int aPhase = gCurrentPattern[pos];
    int powPhase = pow(2, phaseIdx);
    if (aPhase & powPhase) {
        gCurrentPattern[pos] -= powPhase;
    } else {
        gCurrentPattern[pos] += powPhase;
    }
}

void setPhaseType(byte phaseIdx, byte pos) {
    byte type = mod(pos, PHASE_TYPE_COUNT + 1);
    if (type < PHASE_TYPE_COUNT) {
        phases[phaseIdx].setType(type);
    } else if (phases[phaseIdx].envlopFreq.getLerpRate() == CONTROL_RATE) {
        phases[phaseIdx].envlopFreq.setLerpRate(AUDIO_RATE);
    } else {
        phases[phaseIdx].envlopFreq.setLerpRate(CONTROL_RATE);
    }
}

bool setPhaseFromMidiBtn(byte phaseIdx, byte key) {
    if (key == 17 || key == 41) {
        gStepMode = (gStepMode + 1) % STEP_COUNT;
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
    } else if (key == 20 || key == 44) {
        // Loop
    } else if (key > 31 && key < 40) {
        if (gMcMode) {
            setPhaseType(phaseIdx, key - 32 + 8);
        } else {
            togglePhase(phaseIdx, key - 32 + 8);
        }
    } else if (key > 7 && key < 16) {
        if (gMcMode) {
            setPhaseType(phaseIdx, key - 8);
        } else {
            togglePhase(phaseIdx, key - 8);
        }
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
    // Serial.print("setPhaseFromMidi: ");
    // Serial.print(phaseIdx);
    // Serial.print(" key: ");
    // Serial.print(optionKey);
    // Serial.print(" dir: ");
    // Serial.println(direction);

    Phase<MAX_NUM_CELLS, STEP_COUNT> *phase = &phases[phaseIdx];

    if (optionKey == 2) {
        currentTableId = mod(currentTableId + direction, getTablesCount());
        setTable(phaseIdx, currentTableId);
    } else if (optionKey == 3 || optionKey == 13) {
        if (gMcMode) {
            phase->freqSteps[gStepMode] =
                between(phase->freqSteps[gStepMode] + direction, -5000, 5000);
        } else {
            phase->frequency = between(phase->frequency + direction, 0, 5000);
        }
    } else if (optionKey == 4 || optionKey == 14) {
        if (phase->type > FREQ_ENV) {
            phase->phasorShift = between(phase->phasorShift + direction, 0, 24);
        } else {
            // this could be only with gMcMode
            phase->freqShift = between(phase->freqShift + direction, 0, 16);
        }
    } else if (optionKey == 5) {
        // free spot
    } else if (optionKey == 6) {
        if (gMcMode) {
            phase->envlopFreq.setTime(
                0, incTime(phase->envlopFreq.getTime(0), direction));
        } else {
            phase->envlop.setTime(0,
                                  incTime(phase->envlop.getTime(0), direction));
        }
    } else if (optionKey == 7) {
        if (gMcMode) {
            phase->envlopFreq.setTime(
                1, incTime(phase->envlopFreq.getTime(1), direction));
        } else {
            phase->envlop.setTime(1,
                                  incTime(phase->envlop.getTime(1), direction));
        }

    } else if (optionKey == 8) {
        if (gMcMode) {
            phase->envlopFreq.setTime(
                2, incTime(phase->envlopFreq.getTime(2), direction));
        } else {
            phase->envlop.setTime(2,
                                  incTime(phase->envlop.getTime(2), direction));
        }
    } else if (optionKey == 15) {
        // free spot
    } else if (optionKey == 16) {
        if (gMcMode) {
            phase->envlopFreq.setLevel(0,
                incLevel(phase->envlopFreq.getLevel(0), direction));
        } else {
            phase->envlop.setLevel(0,
                incLevel(phase->envlop.getLevel(0), direction));
        }

    } else if (optionKey == 17) {
        if (gMcMode) {
            phase->envlopFreq.setLevel(1,
                incLevel(phase->envlopFreq.getLevel(1), direction));
        } else {
            phase->envlop.setLevel(1,
                incLevel(phase->envlop.getLevel(1), direction));
        }

    } else if (optionKey == 18) {
        if (gMcMode) {
            phase->envlopFreq.setLevel(2,
                incLevel(phase->envlopFreq.getLevel(2), direction));
        } else {
            phase->envlop.setLevel(2,
                incLevel(phase->envlop.getLevel(2), direction));
        }
    }
}

void setStepPattern(byte step, int val) { gCurrentPattern[step] = val; }

void assignCurrentPattern(byte index) {
    gCurrentPatternId = index % MAX_PATTERNS;
    for (int i = 0; i < STEP_COUNT; i++) {
        gCurrentPattern[i] = gSeqPhases[gCurrentPatternId][i];
    }
}
