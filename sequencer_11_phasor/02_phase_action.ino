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
    } else if (phases[phaseIdx].adsrFreq.getLerpRate() == CONTROL_RATE) {
        phases[phaseIdx].adsrFreq.setLerpRate(AUDIO_RATE);
    } else {
        phases[phaseIdx].adsrFreq.setLerpRate(CONTROL_RATE);
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
        currentTableId = mod(currentTableId + direction, 20);
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
        if (gMcMode) {
            phase->adsrFreq.setAttackTime(
                incTime(phase->adsrFreq.getTime(ATTACK), direction));
        } else {
            phase->adsr.setAttackTime(
                incTime(phase->adsr.getTime(ATTACK), direction));
        }
    } else if (optionKey == 6) {
        if (gMcMode) {
            phase->adsrFreq.setDecayTime(
                incTime(phase->adsrFreq.getTime(DECAY), direction));
        } else {
            phase->adsr.setDecayTime(
                incTime(phase->adsr.getTime(DECAY), direction));
        }
    } else if (optionKey == 7) {
        if (gMcMode) {
            phase->adsrFreq.setSustainTime(
                incTime(phase->adsrFreq.getTime(SUSTAIN), direction));
        } else {
            phase->adsr.setSustainTime(
                incTime(phase->adsr.getTime(SUSTAIN), direction));
        }

    } else if (optionKey == 8) {
        if (gMcMode) {
            phase->adsrFreq.setReleaseTime(
                incTime(phase->adsrFreq.getTime(RELEASE), direction));
        } else {
            phase->adsr.setReleaseTime(
                incTime(phase->adsr.getTime(RELEASE), direction));
        }
    } else if (optionKey == 15) {
        if (gMcMode) {
            phase->adsrFreq.setAttackLevel(
                incLevel(phase->adsrFreq.getLevel(ATTACK), direction));
        } else {
            phase->adsr.setAttackLevel(
                incLevel(phase->adsr.getLevel(ATTACK), direction));
        }

    } else if (optionKey == 16) {
        if (gMcMode) {
            phase->adsrFreq.setDecayLevel(
                incLevel(phase->adsrFreq.getLevel(DECAY), direction));
        } else {
            phase->adsr.setDecayLevel(
                incLevel(phase->adsr.getLevel(DECAY), direction));
        }

    } else if (optionKey == 17) {
        if (gMcMode) {
            phase->adsrFreq.setSustainLevel(
                incLevel(phase->adsrFreq.getLevel(SUSTAIN), direction));
        } else {
            phase->adsr.setSustainLevel(
                incLevel(phase->adsr.getLevel(SUSTAIN), direction));
        }

    } else if (optionKey == 18) {
        if (gMcMode) {
            phase->adsrFreq.setReleaseLevel(
                incLevel(phase->adsrFreq.getLevel(RELEASE), direction));
        } else {
            phase->adsr.setReleaseLevel(
                incLevel(phase->adsr.getLevel(RELEASE), direction));
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
