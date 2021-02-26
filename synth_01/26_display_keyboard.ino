byte keyboard_tone = TONE_A;
byte keyboard_base_note = _C4;
byte keyboard_note_pressed = 0;

void displayKeyboard() {
    display.clearDisplay();
    display.setCursor(0, 0);
    dprintln("Keyboard  %s%d  Tone %c", getNoteStr(keyboard_base_note),
             getNoteOctave(keyboard_base_note), getToneChar(keyboard_tone));

    if (keyboard_note_pressed) {
        display.println();
        display.setTextSize(4);
        display.print(getNoteStr(keyboard_note_pressed));
        display.println(getNoteOctave(keyboard_note_pressed));
        display.setTextSize(1);
    }
}