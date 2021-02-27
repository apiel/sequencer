void handlePress(byte key) {
    if (key == 22 || key == 46) {
        kick.noteOn();
    }
}

void handleUp(byte key) {
    if (key == 22 || key == 46) {
        kick.noteOff();
    }
}
