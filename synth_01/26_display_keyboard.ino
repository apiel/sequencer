byte keyboard_tone = TONE_A;

void displayKeyboard() {
    display.clearDisplay();
    display.setCursor(0, 0);
    dprintln("Keyboard     Tone %c", getToneChar(keyboard_tone));
}