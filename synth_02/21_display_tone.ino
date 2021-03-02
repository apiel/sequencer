
void displayTone() {
    display.clearDisplay();
    display.setCursor(0, 0);

    diplayToneType(6 + 2 * 8);
    displayToneSettings(0);
    displayEnvelope(4 + 3 * 8);
    displayFreqModulation(6);
}

void diplayToneType(byte yAbsPos) {
    display.setFont(&Picopixel);

    if (tone->isDrum) {
        dprintxyAbs(53, yAbsPos, "Drum %d", tone->id);
    } else {
        dprintxyAbs(52, yAbsPos, "Synth %d", tone->id);
    }
    display.drawLine(0, yAbsPos, 40, yAbsPos, WHITE);
    display.drawLine(88, yAbsPos, 128, yAbsPos, WHITE);

    display.setFont();
}

void displayToneSettings(byte yPos) {
    dprintxy(0, yPos, tone->tableName);
    dprintxy(10, yPos, "%d", tone->frequency);
    if (tone->type == REVERB) {
        dprintxy(15, yPos, "Reverb");
    } else if (tone->type == SAMPLE) {
        dprintxy(15, yPos, "Sample");
    } else if (tone->type == PHASOR2) {
        dprintxy(14, yPos, "Phasor2");
    } else if (tone->type == PHASOR3) {
        dprintxy(14, yPos, "Phasor3");
    } else {
        dprintxy(15, yPos, "Simple");
    }

    if (tone->type == PHASOR2 || tone->type == PHASOR3) {
        dprintxy(0, yPos + 1, "Shift %d", tone->phasorShift);
    } else {
        dprintxy(0, yPos + 1, "Shift %d", tone->freqShift);
    }
    dprintxy(10, yPos + 1, "Lerp %d", tone->envlopFreq.getLerpRate());
}

void displayEnvelope(byte yAbsPos) {
    if (tone->type == SAMPLE) {
        dprintxyAbs(0, yAbsPos, "Start %d", tone->sample.start_pos);
        dprintxyAbs(0, yAbsPos + 8, "End %d", tone->sample.end_pos);
    } else {
        dprintxyAbs(0, yAbsPos, "A %d", tone->envlop.getTime(0));
        dprintxyAbs(10 * 6, yAbsPos, "S %d", tone->envlop.getTime(1));

        dprintxyAbs(0, yAbsPos + 8, "R %d", tone->envlop.getTime(2));
        dprintxyAbs(10 * 6, yAbsPos + 8, "Level %d", tone->envlop.getLevel(0));
    }
}

void displayFreqModulation(byte yPos) {
    dprintxy(0, yPos, "T");
    dprintxy(0, yPos + 1, "F");
    display.fillRect(5, (yPos + (gMcMode ? 1 : 0)) * 8 + 4, 2, 2, WHITE);
    displayPhase(yPos, 0);
    displayPhase(yPos, 1);
    displayPhase(yPos, 2);
    displayPhase(yPos, 3);
    displayPhase(yPos, 4);
    displayPhase(yPos, 5);
}

void displayPhase(byte yPos, byte id) {
    byte T = yPos * 8;
    byte F = (yPos + 1) * 8;
    byte x = 8 + id * 20;

    display.drawLine(x, T, x, F + 8, WHITE);

    dprintxyTimePct(x + 2, T,
                    (float)tone->envlopFreq.getTime(id) /
                        (float)tone->envlop.getTotalTime());
    display.setFont(&Picopixel);
    int freqAdd = tone->envlopFreq.getLevel(id) - FREQ_ENV_BASE;
    if (freqAdd < 0) {
        dprintxyAbs(x + 2, F + 6, "%d", freqAdd);
    } else {
        dprintxyAbs(x + 2, F + 6, "+%d", freqAdd);
    }
    display.setFont();
}

void dprintxyTimePct(byte x, byte y, float value) {
    if (value < 1) {
        byte f = value * 100;
        display.setCursor(x + 2, y);
        display.print(f);
        display.drawPixel(x, y + 6, WHITE);
    } else {
        display.setCursor(x, y);
        byte i = (byte)value;
        display.print(i);
        display.setCursor(x + 8, y);
        byte f = (value - i) * 10;
        display.print(f);
        display.drawPixel(x + 6, y + 6, WHITE);
    }
}
