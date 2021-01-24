
void toggleDrum(byte drum, byte pos) {
    int aDrum = gCurrentPattern[pos];
    int powDrum = pow(2, drum);
    if (aDrum & powDrum) {
        gCurrentPattern[pos] -= powDrum;
    } else {
        gCurrentPattern[pos] += powDrum;
    }
}

void setDrumFromMidiBtn(byte drum, byte optionKey) {
    if (optionKey == 0) {
        // ToDo change phase type
        // gDrum[drum].useFreqEnvelope = !gDrum[drum].useFreqEnvelope;
    } else if (optionKey == 1) {
        if (phases[drum].freqShift > 0) {
            phases[drum].freqShift--;
        }
    } else if (optionKey == 2) {
        if (phases[drum].freqShift < 16) {
            phases[drum].freqShift++;
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

    // ToDo...
    // here we have to set gDrum[drum].adsr.setAttack...

    // if (optionKey == 2) {
    //     currentTableId = mod(currentTableId + direction, 24);
    //     setTable(drum, currentTableId);
    // } else if (optionKey == 3) {
    //     gDrum[drum].PeakLevel =
    //         between(gDrum[drum].PeakLevel + direction, 0, 250);
    // } else if (optionKey == 4) {
    //     gDrum[drum].SustainLevel =
    //         between(gDrum[drum].SustainLevel + direction, 0, 250);
    // } else if (optionKey == 5) {
    //     gDrum[drum].ATime = between(gDrum[drum].ATime + direction, 0, 100);
    // } else if (optionKey == 6) {
    //     gDrum[drum].DTime = between(gDrum[drum].DTime + direction, 0, 100);
    // } else if (optionKey == 7) {
    //     gDrum[drum].STime = between(gDrum[drum].STime + direction, 0, 100);
    // } else if (optionKey == 8) {
    //     gDrum[drum].RTime = between(gDrum[drum].RTime + direction, 0, 100);
    // } else if (optionKey == 12) {
    //     gDrum[drum].frequency =
    //         between(gDrum[drum].frequency + direction, 0, 2000);
    // } else if (optionKey == 13) {
    //     gDrum[drum].AFreqLevel =
    //         between(gDrum[drum].AFreqLevel + direction, 0, 255);
    // } else if (optionKey == 14) {
    //     gDrum[drum].SFreqLevel =
    //         between(gDrum[drum].SFreqLevel + direction, 0, 255);
    // } else if (optionKey == 15) {
    //     gDrum[drum].RFreqLevel =
    //         between(gDrum[drum].RFreqLevel + direction, 0, 255);
    // } else if (optionKey == 16) {
    //     gDrum[drum].AFreqTime =
    //         between(gDrum[drum].AFreqTime + direction, 0, 100);
    // } else if (optionKey == 17) {
    //     gDrum[drum].SFreqTime =
    //         between(gDrum[drum].SFreqTime + direction, 0, 100);
    // } else if (optionKey == 18) {
    //     gDrum[drum].RFreqTime =
    //         between(gDrum[drum].RFreqTime + direction, 0, 100);
    // }

    // if (optionKey != 2 && optionKey != 12) {
    //     applySetting(drum);
    // }
}

void playDrum() {
    int aDrum = gCurrentPattern[gSeqDrumIndex];

    for (int i = 0; i < DRUMS_COUNT; i++) {
        if (aDrum & (int)pow(2, i)) {
            phases[i].noteOn();
        }
    }
}

void setStepPattern(byte step, int val) { gCurrentPattern[step] = val; }

void assignCurrentPattern(byte index) {
    gCurrentPatternId = index % MAX_PATTERNS;
    for (int i = 0; i < MAX_DRUMS; i++) {
        gCurrentPattern[i] = gSeqDrums[gCurrentPatternId][i];
    }
}
