
void displayTone() {
    display.clearDisplay();
    display.setCursor(0, 0);

    display.println(tone->tableName);
    dprintxy(10, 0, "%d", tone->frequency);
    if (tone->type == REVERB) {
        dprintxy(15, 0, "Reverb");
    } else if (tone->type == SAMPLE) {
        dprintxy(15, 0, "Sample");
    } else if (tone->type == PHASOR2) {
        dprintxy(14, 0, "Phasor2");
    } else if (tone->type == PHASOR3) {
        dprintxy(14, 0, "Phasor3");
    } else {
        dprintxy(15, 0, "Simple");
    }

    if (tone->type == PHASOR2 || tone->type == PHASOR3) {
        dprintxy(0, 1, "Shift %d", tone->phasorShift);
    } else {
        dprintxy(0, 1, "Shift %d", tone->freqShift);
    }
    dprintxy(10, 1, "Lerp %d", tone->envlopFreq.getLerpRate());

    if (tone->type == SAMPLE) {
        dprintxyAbs(0, 4 + 2 * 8, "Start %d", tone->sample.start_pos);
        dprintxyAbs(0, 4 + 3 * 8, "End %d", tone->sample.end_pos);
    } else {
        dprintxyAbs(0, 4 + 2 * 8, "A %d", tone->envlop.getTime(0));
        dprintxyAbs(10 * 6, 4 + 2 * 8, "S %d", tone->envlop.getTime(1));

        dprintxyAbs(0, 4 + 3 * 8, "R %d", tone->envlop.getTime(2));
        dprintxyAbs(10 * 6, 4 + 3 * 8, "Level %d", tone->envlop.getLevel(0));
    }

    dprintxy(0, 5, "T");
    dprintxy(0, 6, "F");
    display.fillRect(5, (gMcMode ? 6 : 5) * 8 + 4, 2, 2, WHITE);
    displayPhase(0);
    displayPhase(1);
    displayPhase(2);
    displayPhase(3);
    displayPhase(4);
    displayPhase(5);
}

void displayPhase(byte id) {
    byte T = 5 * 8;
    byte F = 6 * 8;
    byte x = 8 + id * 20;

    display.drawLine(x, T, x, F + 8, WHITE);

    dprintxyTimePct(
        x + 2, T,
        (float)tone->envlopFreq.getTime(id) / (float)tone->envlop.getTotalTime());
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
