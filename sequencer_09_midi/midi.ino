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
        Serial.print("midi knob: ");
        Serial.print(key);
        Serial.print(',');
        int add = 0;
        byte knob = key % KNOB_COUNT;
        if (knobValues[knob] == KNOB_INIT_VALUE) {
            knobValues[knob] = val;
        } else if (val == 0) {
            add = -1;
            knobValues[knob] = 0;
        } else if (val == KNOB_MAX_VALUE) {
            add = 1;
            knobValues[knob] = KNOB_MAX_VALUE;
        } else {
            add = val - knobValues[knob];
            knobValues[knob] =
                between(knobValues[knob] + add, 0, KNOB_MAX_VALUE);
        }
        Serial.print(add);
        Serial.print(" new value: ");
        Serial.println(knobValues[knob]);

        // button press
    } else if (type == 154) {
        Serial.print("midi btn press: ");
        Serial.print(key);
        Serial.print(',');
        Serial.println(val);
        // button up
    } else if (type == 138) {
        Serial.print("midi btn up: ");
        Serial.print(key);
        Serial.print(',');
        Serial.println(val);
    }
}