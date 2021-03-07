/*
need to be able to see the related Tone
*/

byte currentPatternView = 0;
byte currentStepSelection = 0;

void displayPattern() {
    display.clearDisplay();
    display.setCursor(0, 0);

    Pattern* pPattern = &patterns[tone->id][currentPatternView];

    dprintln("%s %d - Pattern %d", tone->isDrum ? "Drum" : "Synth", tone->id,
             currentPatternView);

    if (playingPatterns[tone->id] == currentPatternView) {
        display.fillTriangle(120, 0, 126, 3, 120, 7, WHITE);
    } else {
        display.fillRect(120, 1, 6, 6, WHITE);
    }

    display.setFont(&Picopixel);
    for (byte pos = 0; pos < STEP_COUNT; pos++) {
        displayStep(pPattern, pos);
    }
    display.setFont();

    displayChains(pPattern);
}

void displayStep(Pattern* pPattern, byte pos) {
    byte x = pos % 8;
    byte y = pos / 8 + 1;

    Step* step = &pPattern->steps[pos];

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

    if (currentStepSelection == pos) {
        display.drawLine(x * 16 + 2, y * 7 + 6, x * 16 + 10, y * 7 + 6, WHITE);
    }
}

void displayChains(Pattern* pPattern) {
    dprintxy(0, 5, "Priority %d", pPattern->priority);
    if (pPattern->counterSetter == LOOP_CHAIN) {
        dprintxy(14, 5, "Set oo");
    } else {
        dprintxy(14, 5, "Set %d", pPattern->counterSetter);
    }

    display.setFont(&Picopixel);

    byte y = 48;
    for (byte c = 0; c < MAX_CHAINED_PATTERN; c++) {
        display.drawLine(c * 16 + 1, y + 7, c * 16 + 12, y + 7, WHITE);
        display.setCursor(c * 16 + 2, y + 5);
        if (pPattern->counters[c] == LOOP_CHAIN) {
            dprint("oo");
        } else {
            dprint("%d", pPattern->counters[c]);
        }
    }
    display.setFont();
}
