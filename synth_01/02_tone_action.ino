bool gMcMode = false;
byte gStepMode = 0;

void setToneType(byte toneIdx, byte pos) {
    byte type = mod(pos, TONE_TYPE_COUNT + 1);
    if (type < TONE_TYPE_COUNT) {
        tones[toneIdx].setType(type);
    } else if (tones[toneIdx].envlopFreq.getLerpRate() == CONTROL_RATE) {
        tones[toneIdx].envlopFreq.setLerpRate(AUDIO_RATE);
    } else {
        tones[toneIdx].envlopFreq.setLerpRate(CONTROL_RATE);
    }
}

bool setToneFromMidiBtn(byte toneIdx, byte key) {
    if (key == 17 || key == 41) {
        gStepMode = (gStepMode + 1) % STEP_COUNT;
    } else if (key == 18 || key == 42) {
        // // we might better use knob for this
        // if (tones[toneIdx].freqShift > 0) {
        //     tones[toneIdx].freqShift--;
        // }
    } else if (key == 19 || key == 43) {
        // // we might better use knob for this
        //  if (tones[toneIdx].freqShift < 16) {
        //     tones[toneIdx].freqShift++;
        // }
    } else if (key == 20 || key == 44) {
        // Loop
    } else if (key > 31 && key < 40) {
        if (gMcMode) {
            setToneType(toneIdx, key - 32 + 8);
        } else {
            // toggleTone(toneIdx, key - 32 + 8);
        }
    } else if (key > 7 && key < 16) {
        if (gMcMode) {
            setToneType(toneIdx, key - 8);
        } else {
            // toggleTone(toneIdx, key - 8);
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

void setToneFromMidiKnob(byte toneIdx, byte optionKey, int direction) {
    // Serial.print("setToneFromMidi: ");
    // Serial.print(toneIdx);
    // Serial.print(" key: ");
    // Serial.print(optionKey);
    // Serial.print(" dir: ");
    // Serial.println(direction);

    Tone<MAX_NUM_CELLS, STEP_COUNT> *tone = &tones[toneIdx];

    if (optionKey == 2) {
        currentTableId = mod(currentTableId + direction, getTablesCount());
        setTable(toneIdx, currentTableId);
    } else if (optionKey == 3 || optionKey == 13) {
        if (gMcMode) {
            tone->freqSteps[gStepMode] =
                between(tone->freqSteps[gStepMode] + direction, -5000, 5000);
        } else {
            tone->frequency = between(tone->frequency + direction, 0, 5000);
        }
    } else if (optionKey == 4 || optionKey == 14) {
        if (tone->type > FREQ_ENV) {
            tone->phasorShift = between(tone->phasorShift + direction, 0, 24);
        } else {
            // this could be only with gMcMode
            tone->freqShift = between(tone->freqShift + direction, 0, 16);
        }
    } else if (optionKey == 5) {
        // free spot
    } else if (optionKey == 6) {
        if (gMcMode) {
            tone->envlopFreq.setTime(
                0, incTime(tone->envlopFreq.getTime(0), direction));
        } else {
            tone->envlop.setTime(0,
                                  incTime(tone->envlop.getTime(0), direction));
        }
    } else if (optionKey == 7) {
        if (gMcMode) {
            tone->envlopFreq.setTime(
                1, incTime(tone->envlopFreq.getTime(1), direction));
        } else {
            tone->envlop.setTime(1,
                                  incTime(tone->envlop.getTime(1), direction));
        }

    } else if (optionKey == 8) {
        if (gMcMode) {
            tone->envlopFreq.setTime(
                2, incTime(tone->envlopFreq.getTime(2), direction));
        } else {
            tone->envlop.setTime(2,
                                  incTime(tone->envlop.getTime(2), direction));
        }
    } else if (optionKey == 15) {
        // free spot
    } else if (optionKey == 16) {
        if (gMcMode) {
            tone->envlopFreq.setLevel(0,
                incLevel(tone->envlopFreq.getLevel(0), direction));
        } else {
            tone->envlop.setLevel(0,
                incLevel(tone->envlop.getLevel(0), direction));
        }

    } else if (optionKey == 17) {
        if (gMcMode) {
            tone->envlopFreq.setLevel(1,
                incLevel(tone->envlopFreq.getLevel(1), direction));
        } else {
            tone->envlop.setLevel(1,
                incLevel(tone->envlop.getLevel(1), direction));
        }

    } else if (optionKey == 18) {
        if (gMcMode) {
            tone->envlopFreq.setLevel(2,
                incLevel(tone->envlopFreq.getLevel(2), direction));
        } else {
            tone->envlop.setLevel(2,
                incLevel(tone->envlop.getLevel(2), direction));
        }
    }
}
