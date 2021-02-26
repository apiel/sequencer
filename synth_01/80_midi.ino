#define MENU_SIZE (MAX_PATTERNS + MAX_TONES + 2)
#define KNOB_COUNT 18
#define KNOB_MAX_VALUE 127
#define KNOB_INIT_VALUE 200

byte knobValues[KNOB_COUNT] = {
    KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE,
    KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE,
    KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE,
    KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE,
    KNOB_INIT_VALUE, KNOB_INIT_VALUE};

const byte MAIN_MENU = mod(-1, MENU_SIZE);
byte currentMenu = MAIN_MENU;

void handleMidi(byte type, byte key, byte val) {
    // knob
    if (type == 186) {
        handleKnob(key, val);
        // button press
    } else if (type == 154) {
        handlePress(key);
        // button up
    } else if (type == 138) {
        Serial.print("midi btn up: ");
        Serial.print(key);
        Serial.print(',');
        Serial.println(val);
        if (isKeyboardMenu()) {
            handleKeyboardFromMidiUp(key);
        }
    }
    // displayUpdate();
}

void handlePress(byte key) {
    // Serial.print("midi btn press: ");
    // Serial.println(key);
    if (currentMenu == MAIN_MENU) {
        if (key > 31 && key < 40) {
            if (gMcMode) {
                setupTones(key - 32 + 8);
            } else {
                // assignCurrentPattern(key - 32 + 8);
            }
        } else if (key > 7 && key < 16) {
            if (gMcMode) {
                setupTones(key - 8);
            } else {
                // assignCurrentPattern(key - 8);
            }
        }
        handleDefaultButton(key);
    } else if (isToneMenu()) {
        if (!setToneFromMidiBtn(currentMenu, key)) {
            handleDefaultButton(key);
        }
    } else if (isPatternMenu()) {
        if (key == 46 || key == 22) {
            byte id = getMenuPatternId();
            if (patterns[id].isPlaying) {
                patterns[id].stop();
            } else {
                patterns[id].play();
            }
        }
    } else if (isKeyboardMenu()) {
        handleKeyboardFromMidiPress(key);
    }
}

void handleDefaultButton(byte key) {
    if (key == 46 || key == 22) {
        togglePlay();
    } else if (key == 40 || key == 16) {
        gMcMode = !gMcMode;
    }
}

bool isToneMenu() { return currentMenu >= 0 && currentMenu < MAX_TONES; }
bool isPatternMenu() {
    return !isToneMenu() && currentMenu < MAX_TONES + MAX_PATTERNS;
}
bool isKeyboardMenu() { return currentMenu == MAX_TONES + MAX_PATTERNS; }

byte getMenuPatternId() { return currentMenu - MAX_TONES; }

char getCurrentToneChar() { return getToneChar(currentMenu); }

char getToneChar(byte menu) {
    // 65 is 'A' position in ascii table
    return menu + 65;
}

byte getCurrentToneIdx() { return currentMenu; }

void handleKnob(byte key, byte val) {
    byte knob = key % KNOB_COUNT;
    int direction = getKnobDirection(knob, val);
    // Serial.print("midi knob: ");
    // Serial.print(knob);
    // Serial.print(',');
    // Serial.print(direction);
    // Serial.print(" new value: ");
    // Serial.println(knobValues[knob]);

    if (knob == 9 || knob == 10) {
        gVolume = val;
    } else if (knob == 1 || knob == 11) {
        currentMenu = mod(currentMenu + direction, MENU_SIZE);
        // Serial.print("Select menu: ");
        // Serial.print(MENU_SIZE);
        // Serial.print(" - dir: ");
        // Serial.print(direction);
        // Serial.print(" - cur: ");
        // Serial.println(currentMenu);
    } else if (isToneMenu()) {
        setToneFromMidiKnob(currentMenu, key, direction);
    } else if (isKeyboardMenu()) {
        handleKeyboardFromMidiKnob(key, direction);
    } else if (currentMenu == MAIN_MENU) {
        if (knob == 2 || knob == 12) {
            increaseBPM(direction);
        } else if (knob == 3 || knob == 13) {
            increaseCutoff(direction);
        } else if (knob == 4 || knob == 14) {
            increaseResonance(direction);
        }
    }
}

int getKnobDirection(byte knob, byte val) {
    int direction = 0;
    if (knobValues[knob] == KNOB_INIT_VALUE) {
        knobValues[knob] = val;
    } else if (val == 0) {
        direction = -1;
        knobValues[knob] = 0;
    } else if (val == KNOB_MAX_VALUE) {
        direction = 1;
        knobValues[knob] = KNOB_MAX_VALUE;
    } else {
        direction = val - knobValues[knob];
        knobValues[knob] =
            between(knobValues[knob] + direction, 0, KNOB_MAX_VALUE);
    }
    return direction;
}

void handleKeyboardFromMidiKnob(byte optionKey, int direction) {
    if (optionKey == 2) {
        keyboard_tone = mod(keyboard_tone + direction, MAX_TONES);
    }
}

void handleKeyboardFromMidiPress(byte key) {
    tones[keyboard_tone].noteOn(NOTE_FREQ[keyboard_base_note + key] -
                                NOTE_FREQ[keyboard_base_note]);
    keyboard_note_pressed = keyboard_base_note + key;
}

void handleKeyboardFromMidiUp(byte key) {
    tones[keyboard_tone].noteOff();
    keyboard_note_pressed = 0;
}
