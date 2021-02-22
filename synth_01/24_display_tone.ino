Tone<MAX_NUM_CELLS> *getCurrentTone() { return &tones[getCurrentToneIdx()]; }

void displayTone() {
    display.clearDisplay();
    display.setCursor(0, 0);
    dprintln("Tone %c", getCurrentToneChar());

    Tone<MAX_NUM_CELLS> *tone = getCurrentTone();

    display.println(tone->tableName);
    dprintln("Freq %d", tone->frequency);
    if (gMcMode) {
        // dprintln("%d-> %d", gStepMode + 1, tone->freqSteps[gStepMode]);
    }

    dprintxyAbs(4, 32, "A");
    dprintxyTimePct(0, 40, tone->envlop.getTime(0));
    dprintxyLevelPct(0, 48, tone->envlop.getLevel(0));

    display.drawLine(15, 32, 15, 55, WHITE);

    dprintxyAbs(21, 32, "S");
    dprintxyTimePct(17, 40, tone->envlop.getTime(1));
    dprintxyLevelPct(17, 48, tone->envlop.getLevel(1));

    display.drawLine(31, 32, 31, 55, WHITE);

    dprintxyAbs(37, 32, "D");
    dprintxyTimePct(33, 40, tone->envlop.getTime(2));
    dprintxyLevelPct(33, 48, tone->envlop.getLevel(2));

    if (tone->type > REVERB) {
        if (gMcMode) {
            display.fillTriangle(82, 33, 82, 38, 84, 35, WHITE);
            display.fillTriangle(98, 33, 98, 38, 100, 35, WHITE);
            display.fillTriangle(114, 33, 114, 38, 116, 35, WHITE);
        } else {
            display.fillTriangle(0, 33, 0, 38, 2, 35, WHITE);
            display.fillTriangle(17, 33, 17, 38, 19, 35, WHITE);
            display.fillTriangle(33, 33, 33, 38, 35, 35, WHITE);
        }

        dprintxyAbs(86, 32, "A");
        dprintxyTimePct(81, 40, tone->envlopFreq.getTime(0));
        dprintxyLevelPct(81, 48, tone->envlopFreq.getLevel(0));

        display.drawLine(95, 32, 95, 55, WHITE);

        dprintxyAbs(102, 32, "S");
        dprintxyTimePct(97, 40, tone->envlopFreq.getTime(1));
        dprintxyLevelPct(97, 48, tone->envlopFreq.getLevel(1));

        display.drawLine(111, 32, 111, 55, WHITE);

        dprintxyAbs(118, 32, "D");
        dprintxyTimePct(113, 40, tone->envlopFreq.getTime(2));
        dprintxyLevelPct(113, 48, tone->envlopFreq.getLevel(2));

        if (tone->type == FREQ_ENV) {
            dprintxy(12, 1, "Freq Env");
            dprintxy(12, 2, "Shift %d", tone->freqShift);
        } else if (tone->type == PHASOR2) {
            dprintxy(12, 1, "Phasor 2");
            dprintxy(12, 2, "Shift %d", tone->phasorShift);
        } else if (tone->type == PHASOR3) {
            dprintxy(12, 1, "Phasor 3");
            dprintxy(12, 2, "Shift %d", tone->phasorShift);
        }
        dprintxy(12, 3, "LR %d", tone->envlopFreq.getLerpRate());
    } else {
        if (tone->type == REVERB) {
            dprintxy(12, 1, "Reverb");
        } else {
            dprintxy(12, 1, "Simple");
        }
    }
    displayTonePattern();
}

void displayLpf() {
    dprintln("Cutoff: %d", gCutoff);
    dprintln("Resonance: %d", gResonance);
}

void displayTonePattern() {
    // byte idx = getCurrentToneIdx();

    // for (byte i = 0, s = 0; i < STEP_COUNT; i++) {
    //     if (i % 4 == 0) s += 3;
    //     int aTone = gCurrentPattern[i];
    //     if (aTone & (int)pow(2, idx)) {
    //         display.fillRect(i * 7 + s, 57, 6, 6, WHITE);
    //     } else {
    //         display.drawRect(i * 7 + s, 57, 6, 6, WHITE);
    //     }
    //     if (i == gSeqStepIndex) {
    //         display.drawLine(i * 7 + 1 + s, 63, i * 7 + 4 + s, 63, WHITE);
    //     }
    // }
}