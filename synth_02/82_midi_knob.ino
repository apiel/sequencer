#define KNOB_COUNT 18

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
    } else if (knob == 1) {
        currentTableId = mod(currentTableId + direction, getTablesCount());
        setTable(currentTableId);
    } else if (knob == 2) {
        kick.frequency = between(kick.frequency + direction, 1, 5000);
    } else if (knob == 3) {
        byte type = mod(kick.type + direction, TONE_TYPE_COUNT);
        kick.setType(type);
    } else if (knob == 4) {
        if (kick.type == PHASOR2 || kick.type == PHASOR3) {
            kick.phasorShift = between(kick.phasorShift + direction, 0, 24);
        } else {
            kick.freqShift = between(kick.freqShift + direction, 0, 16);
        }
    } else if (knob == 5) {
        if (kick.type == SAMPLE) {
            kick.sample.setStart(
                between(kick.sample.start_pos + (direction * 10), 0,
                        kick.sample.end_pos));
        } else {
            kick.envlop.setTime(
                0, between(kick.envlop.getTime(0) + direction, 0, 60000));
        }
    } else if (knob == 6) {
        if (kick.type == SAMPLE) {
            kick.sample.setEnd(between(kick.sample.end_pos + (direction * 10),
                                       kick.sample.start_pos, NUM_TABLE_CELLS));
        } else {
            kick.envlop.setTime(
                1, between(kick.envlop.getTime(1) + direction, 0, 60000));
        }
    } else if (knob == 7) {
        kick.envlop.setTime(
            2, between(kick.envlop.getTime(2) + direction, 0, 60000));
    } else if (knob == 8) {
        kick.envlop.setLevel(
            0, between(kick.envlop.getLevel(0) + direction, 0, 255));
    } else if (knob >= 11 && knob <= 16) {
        if (gMcMode) {
            kick.envlopFreq.setLevel(
                knob - 11,
                between(kick.envlopFreq.getLevel(knob - 11) + direction, 0,
                        255));
        } else {
            kick.incFreqTime(knob - 11, direction);
        }
    }
}

// void increaseCutoff(int direction) {
//     gCutoff = (byte)between(gCutoff + (direction * 2), 0, 255);
//     lpf.setCutoffFreq(gCutoff);
//     // Serial.print("Set gCutoff ");
//     // Serial.println(gCutoff);
// }

// void increaseResonance(int direction) {
//     gResonance = (byte)between(gResonance + (direction * 2), 0, 255);
//     lpf.setResonance(gResonance);
//     // Serial.print("Set gResonance ");
//     // Serial.println(gResonance);
// }
