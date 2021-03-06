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
    }
    // displayUpdate();
}

void handlePress(byte key) {
    // Serial.print("midi btn press: ");
    // Serial.println(key);
    if (currentMenu == MAIN_MENU) {
        if (key > 31 && key < 40) {
            if (gMcMode) {
                setupPhases(key - 32 + 8);
            } else {
                assignCurrentPattern(key - 32 + 8);
            }
        } else if (key > 7 && key < 16) {
            if (gMcMode) {
                setupPhases(key - 8);
            } else {
                assignCurrentPattern(key - 8);
            }
        }
        handleDefaultButton(key);
    } else if (isPhaseMenu()) {
        if (!setPhaseFromMidiBtn(currentMenu, key)) {
            handleDefaultButton(key);
        }
    }
}

void handleDefaultButton(byte key) {
    if (key == 46 || key == 22) {
        togglePlay();
    } else if (key == 40 || key == 16) {
        gMcMode = !gMcMode;
    }
}

bool isPhaseMenu() { return currentMenu >= 0 && currentMenu < MAX_PHASES; }

char getCurrentPhaseChar() {
    // 65 is 'A' position in ascii table
    return currentMenu + 65;
}

byte getCurrentPhaseIdx() { return currentMenu; }

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
    } else if (isPhaseMenu()) {
        setPhaseFromMidiKnob(currentMenu, key, direction);
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
