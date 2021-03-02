void handlePress(byte key) {
    if (key == 22 || key == 46) {
        tone.noteOn();
    } else if (key == 17 || key == 41) {
        if (tone.envlopFreq.getLerpRate() == CONTROL_RATE) {
            tone.envlopFreq.setLerpRate(AUDIO_RATE);
        } else {
            tone.envlopFreq.setLerpRate(CONTROL_RATE);
        }
    } else if (key == 16 || key == 40) {
        gMcMode = !gMcMode;
    }
}

void handleUp(byte key) {}
