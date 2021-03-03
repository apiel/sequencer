void pattern_handlePress(byte key) {
    byte toneId = getItemKey(key);
    if (toneId < MAX_TONES) {
        tone = &tones[toneId];
    } else if (key == 22 || key == 46) {
        // here we should toggle active pattern
        if (playingPatterns[tone->id] == currentPatternView) {
            playingPatterns[tone->id] = PATTERN_STOP;
        } else {
            playingPatterns[tone->id] = currentPatternView;
        }
    } else {
        default_handlePress(key);
    }
}

void pattern_handleUp(byte key) {
}

void pattern_handleKnob(byte key, byte val) {
    byte knob = key % KNOB_COUNT;
    int direction = getKnobDirection(knob, val);
    
    if (knob == 1) {
        currentPatternView = mod(currentPatternView + direction, MAX_PATTERNS);
    } else {
        default_handleKnob(key, val);
    }
}
