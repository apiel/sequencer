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
