void handlePress(byte key) {
    if (key == 22 || key == 46) {
        kick.noteOn();
    } else if (key == 8 || key == 32) {
        if (kick.envlopFreq.getLerpRate() == CONTROL_RATE) {
            kick.envlopFreq.setLerpRate(AUDIO_RATE);
        } else {
            kick.envlopFreq.setLerpRate(CONTROL_RATE);
        }
    } else if (key == 16 || key == 40) {
        gMcMode = !gMcMode;
    }
}

void handleUp(byte key) {}
