#include <Fonts/Picopixel.h>

void displayPattern() {
    display.clearDisplay();
    display.setCursor(0, 0);
    byte id = getMenuPatternId();
    display.println(patterns[id].name);

    display.setFont(&Picopixel);

    for (byte pos = 0; pos < STEP_COUNT; pos++) {
        displayStep(id, pos);
    }

    display.setFont();
}

void displayStep(byte id, byte pos) {
    byte x = pos % 8;
    byte y = pos / 8 + 1;

    Step* step = &patterns[id].steps[pos];

    display.drawLine(x * 16 + 1, y * 7 + 7, x * 16 + 12, y * 7 + 7,
                     WHITE);
    if (step->duration) {
        display.setCursor(x * 16 + 2, y * 7 + 5);
        dprint("%s%d", getNoteDot(step->note), getNoteOctave(step->note));
    }

    if (gSeqStepIndex == pos) {
        display.drawLine(x * 16 + 2, y * 7 + 6, x * 16 + 10, y * 7 + 6,
                         WHITE);
    }
}