
void togglePlay() {
    if (gSeqPlay) {
        stop();
    } else {
        play();
    }
}

void play() {
    gSeqPlay = true;
    gSeqPhaseIndex = 0;
}

void stop() { gSeqPlay = false; }

void increaseBPM(int direction) {
    setTempo((byte)between(gBPM + direction, 10, 255));
    Serial.print("Set new bpm ");
    Serial.println(gBPM);
}

void setTempo(byte bpm) {
    gBPM = between(bpm, 10, 255);
    // 4 ♬ ♬ phase per beat in 60000ms = 1min
    gTempo = 60000 / (gBPM * 4);

    // Serial.print("Set tempo ");
    // Serial.println(gTempo);
}

void increaseCutoff(int direction) {
    gCutoff = (byte)between(gCutoff + (direction * 2), 0, 255);
    lpf.setCutoffFreq(gCutoff);
    // Serial.print("Set gCutoff ");
    // Serial.println(gCutoff);
}

void increaseResonance(int direction) {
    gResonance = (byte)between(gResonance + (direction * 2), 0, 255);
    lpf.setResonance(gResonance);
    // Serial.print("Set gResonance ");
    // Serial.println(gResonance);
}
