void handleMidi(byte type, byte key, byte val) {
    // knob
    if (type == 186) {
        Serial.print("midi knob: ");
        Serial.print(key);
        Serial.print(',');
        Serial.println(val);
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