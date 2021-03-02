#define KNOB_COUNT 18

void handleMidi(byte type, byte key, byte val) {
    if (type == 186) {
        if (currentView == VIEW_TONE) {
            tone_handleKnob(key, val);
        } else if (currentView == VIEW_KEYBOARD) {
            kb_handleKnob(key, val);
        }
    } else if (type == 154) {
        if (currentView == VIEW_TONE) {
            tone_handlePress(key);
        } else if (currentView == VIEW_KEYBOARD) {
            kb_handlePress(key);
        }
    } else if (type == 138) {
        if (currentView == VIEW_TONE) {
            tone_handleUp(key);
        } else if (currentView == VIEW_KEYBOARD) {
            kb_handleUp(key);
        }
    }
    displayUpdate();
}

void default_handlePress(byte key) {
    if (key == 16 || key == 40) {
        gMcMode = !gMcMode;
    } else if (key == 18 || key == 42) {
        currentView = (currentView - 1) % VIEW_COUNT;
    } else if (key == 19 || key == 43) {
        currentView = (currentView + 1) % VIEW_COUNT;
    }
}

void default_handleKnob(byte knob, byte val) {
    if (knob == 9 || knob == 10) {
        gVolume = val;
    }
}
