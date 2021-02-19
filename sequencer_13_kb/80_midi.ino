#define KNOB_COUNT 18
#define KNOB_MAX_VALUE 127
#define KNOB_INIT_VALUE 200

byte knobValues[KNOB_COUNT] = {
    KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE,
    KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE,
    KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE,
    KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE,
    KNOB_INIT_VALUE, KNOB_INIT_VALUE};

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
        handleUp(key);
    }
}

void handlePress(byte key) {
    if (key == 46 || key == 22) {
        gSeqPlay = !gSeqPlay;
    } else if (key == 8) {
        phase.setType(SIMPLE);
    } else if (key == 9) {
        phase.setType(REVERB);
    } else if (key == 10) {
        phase.setType(FREQ_ENV);
    } else if (key == 11) {
        phase.setType(PHASOR2);
    } else if (key == 12) {
        phase.setType(PHASOR3);
    } else if (key == 15) {
        phase.noteOn(1);
        phase.envlop.loop(1);
    }
}

void handleUp(byte key) {
    if (key == 15) {
        phase.envlop.stop();
    }
}

void handleKnob(byte key, byte val) {
    byte knob = key % KNOB_COUNT;
    int direction = getKnobDirection(knob, val);

    if (knob == 1 || knob == 11) {
        // currentMenu = mod(currentMenu + direction, MENU_SIZE);
        // Serial.print("Select menu: ");
        // Serial.print(MENU_SIZE);
        // Serial.print(" - dir: ");
        // Serial.print(direction);
        // Serial.print(" - cur: ");
        // Serial.println(currentMenu);
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
