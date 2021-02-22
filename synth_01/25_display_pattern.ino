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
    byte y = pos / 8;

    Step* step = &patterns[id].steps[pos];

    if (step->duration) {
        display.drawRect(x * 16, y * 8 + 8, 14, 7, WHITE);
        display.setCursor(x * 16 + 2, y * 8 + 5 + 8);
        display.print(step->note);
    } else {
        display.drawLine(x * 16, y * 8 + 8 + 7, x * 16 + 14, y * 8 + 8 + 7,
                         WHITE);
    }
}