void handleMidi(byte type, byte key, byte val) {
    if (type == 186) {
        handleKnob(key, val);
    } else if (type == 154) {
        handlePress(key);
    } else if (type == 138) {
        handleUp(key);
    }
}
