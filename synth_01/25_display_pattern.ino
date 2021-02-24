#include <Fonts/Picopixel.h>

void displayPattern() {
    display.clearDisplay();
    display.setCursor(0, 0);
    byte id = getMenuPatternId();
    display.println(patterns[id].name);

    if (patterns[id].isPlaying) {
        display.fillTriangle(120, 0, 126, 3, 120, 7, WHITE);
    } else {
        display.fillRect(120, 1, 6, 6, WHITE);
    }

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

    display.drawLine(x * 16 + 1, y * 7 + 7, x * 16 + 12, y * 7 + 7, WHITE);
    if (step->duration) {
        display.setCursor(x * 16 + 2, y * 7 + 5);
        dprint("%s%d", getNoteDot(step->note), getNoteOctave(step->note));

        // this show the duration but will be buggy when note go on the next
        // line need to think about a solution
        for (byte d = 1; d < step->duration; d++) {
            display.drawLine(d * (x + 1) * 16 - 4, y * 7 + 6,
                             d * (x + 1) * 16 - 4 + 5, y * 7 + 6, WHITE);
        }
    }

    if (gSeqStepIndex == pos) {
        display.drawLine(x * 16 + 2, y * 7 + 6, x * 16 + 10, y * 7 + 6, WHITE);
    }
}