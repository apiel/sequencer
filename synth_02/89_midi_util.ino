#define KNOB_MAX_VALUE 127
#define KNOB_INIT_VALUE 200

byte knobValues[KNOB_COUNT] = {
    KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE,
    KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE,
    KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE,
    KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE, KNOB_INIT_VALUE,
    KNOB_INIT_VALUE, KNOB_INIT_VALUE};

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

// used for first row from x touch mini to know which item
// number is it, e.g. which tone selected
byte getItemKey(byte key) {
    if (key >= 8 && key <= 15) {
        return key - 8;
    }
    if (key >= 32 && key <= 39) {
        return key - 32;
    }
    return 255;
}

