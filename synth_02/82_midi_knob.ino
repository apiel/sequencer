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
        tone.frequency = between(tone.frequency + direction, 1, 5000);
    } else if (knob == 3) {
        byte type = mod(tone.type + direction, TONE_TYPE_COUNT);
        tone.setType(type);
    } else if (knob == 4) {
        if (tone.type == PHASOR2 || tone.type == PHASOR3) {
            tone.phasorShift = between(tone.phasorShift + direction, 0, 24);
        } else {
            tone.freqShift = between(tone.freqShift + direction, 0, 16);
        }
    } else if (knob == 5) {
        if (tone.type == SAMPLE) {
            tone.sample.setStart(
                between(tone.sample.start_pos + (direction * 10), 0,
                        tone.sample.end_pos));
        } else {
            tone.envlop.setTime(
                0, between(tone.envlop.getTime(0) + direction, 0, 60000));
        }
    } else if (knob == 6) {
        if (tone.type == SAMPLE) {
            tone.sample.setEnd(between(tone.sample.end_pos + (direction * 10),
                                       tone.sample.start_pos, NUM_TABLE_CELLS));
        } else {
            tone.envlop.setTime(
                1, between(tone.envlop.getTime(1) + direction, 0, 60000));
        }
    } else if (knob == 7) {
        tone.envlop.setTime(
            2, between(tone.envlop.getTime(2) + direction, 0, 60000));
    } else if (knob == 8) {
        tone.envlop.setLevel(
            0, between(tone.envlop.getLevel(0) + direction, 0, 255));
    } else if (knob >= 11 && knob <= 16) {
        if (gMcMode) {
            tone.envlopFreq.setLevel(
                knob - 11,
                between(tone.envlopFreq.getLevel(knob - 11) + direction, 0,
                        255));
        } else {
            tone.incFreqTime(knob - 11, direction);
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
