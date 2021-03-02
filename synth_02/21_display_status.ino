
void displayStatus() {
    if (gSeqPlay) {
        display.fillTriangle(100, 0, 106, 3, 100, 7, WHITE);
    } else {
        display.fillRect(100, 1, 6, 6, WHITE);
    }
    // dprintxy(18, 0, "%d", gSeqStepIndex+1);
    for (byte i = 0; i < gSeqStepIndex + 1; i++) {
        // display.fillRect(68 + (i%8) * 4, i >= 8 ? 0 : 5, 2, 2, WHITE);
        byte y = 0;
        if (i > 11)
            y = 6;
        else if (i > 7)
            y = 4;
        else if (i > 3)
            y = 2;
        display.fillRect(82 + (i % 4) * 4, y, 2, 1, WHITE);
    }
    display.drawTriangle(110, 6, 127, 6, 127, 0, WHITE);
    display.fillTriangle(110, 6, 110 + (17 * gVolume / MAX_VOLUME), 6,
                         110 + (17 * gVolume / MAX_VOLUME),
                         6 - (6 * gVolume / MAX_VOLUME), WHITE);

    if (gMcMode) {
        display.setCursor(66, 0);
        display.setTextColor(BLACK, WHITE);
        display.print("mc");
        display.setTextColor(WHITE);
        display.drawLine(65, 0, 65, 7, WHITE);
    }
}
