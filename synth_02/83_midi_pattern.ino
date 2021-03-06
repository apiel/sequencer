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
    } else if (key == 23 || key == 47) {
        savePatternToStorage(tone->id, currentPatternView);
    } else {
        default_handlePress(key);
    }
}

void pattern_handleUp(byte key) {}

void pattern_handleKnob(byte key, byte val) {
    byte knob = key % KNOB_COUNT;
    int direction = getKnobDirection(knob, val);

    if (knob == 1) {
        currentPatternView = mod(currentPatternView + direction, MAX_PATTERNS);
    } else if (knob == 2) {
        currentStepSelection =
            mod(currentStepSelection + direction, STEP_COUNT);
    } else if (knob == 3) {
        Step* pStep =
            &patterns[tone->id][currentPatternView].steps[currentStepSelection];
        // Instead of STEP_COUNT could try to find the next...
        pStep->duration = between(pStep->duration + direction, 0, STEP_COUNT);
    } else if (knob == 4) {
        Step* pStep =
            &patterns[tone->id][currentPatternView].steps[currentStepSelection];
        pStep->set(between(pStep->note + direction, _C0, _B8));
    } else {
        default_handleKnob(key, val);
    }
}
