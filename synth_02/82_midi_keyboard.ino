void kb_handlePress(byte key) {
    byte noteId = getItemKey(key);
    if (noteId < 255) {
        tone->noteOn(NOTE_FREQ[keyboard_base_note + key] -
                                    NOTE_FREQ[keyboard_base_note]);
        keyboard_note_pressed = keyboard_base_note + key;
    } else {
        default_handlePress(key);
    }
}

void kb_handleUp(byte key) {
    byte noteId = getItemKey(key);
    if (noteId < 255) {
        if (!tone->isDrum) {
            tone->noteOff();
        }
        keyboard_note_pressed = 0;
    }
}

void kb_handleKnob(byte key, byte val) {
    byte knob = key % KNOB_COUNT;
    int direction = getKnobDirection(knob, val);

    if (key == 1) {
        keyboard_base_note = mod(keyboard_base_note + direction, _B8);
    } else if (key == 2) {
        tone = &tones[mod(tone->id + direction, MAX_TONES)];
    } else {
        default_handleKnob(key, val);
    }
}
