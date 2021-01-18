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
}

void handlePress(byte key) {
    // Serial.print("midi btn press: ");
    // Serial.println(key);
    if (currentMenu == MAIN_MENU) {
        handleDefaultButton(key);
    } else if (isNoteMenu()) {
        if (key == 33 || key == 9) {
            Serial.println("Set double envelop");
            setNoteFromMidi(currentMenu, 0, 2);
        } else if (key == 32 || key == 8) {
            Serial.println("Set simple envelop");
            setNoteFromMidi(currentMenu, 0, 1);
        } else {
            handleDefaultButton(key);
        }
    }
}

void handleDefaultButton(byte key) {
    if (key == 46 || key == 22) {
        play();
    } else if (key == 45 || key == 21) {
        stop();
    } else if (key == 38 || key == 14) {
        gSeqMute = true;
    } else if (key == 37 || key == 13) {
        gSeqMute = false;
    }
}

bool isNoteMenu() { return currentMenu >= 0 && currentMenu < NOTES_COUNT; }

void handleKnob(byte key, byte val) {
    byte knob = key % KNOB_COUNT;
    int direction = getKnobDirection(knob, val);
    // Serial.print("midi knob: ");
    // Serial.print(knob);
    // Serial.print(',');
    // Serial.print(direction);
    // Serial.print(" new value: ");
    // Serial.println(knobValues[knob]);

    if (knob == 1 || knob == 11) {
        currentMenu = mod(currentMenu + direction, MENU_SIZE);
        Serial.print("Select menu: ");
        // Serial.print(MENU_SIZE);
        // Serial.print(" - dir: ");
        // Serial.print(direction);
        // Serial.print(" - cur: ");
        Serial.println(currentMenu);
    } else if (isNoteMenu()) {
        setNoteFromMidi(currentMenu, key, direction);
    } else if (currentMenu == MAIN_MENU) {
        if (knob == 2 || knob == 12) {
            increaseBPM(direction);
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
