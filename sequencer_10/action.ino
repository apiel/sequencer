
void togglePlay() {
    if (gSeqPlay) {
        stop();
    } else {
        play();
    }
}

void play() {
    gSeqPlay = true;
    gSeqDrumIndex = 0;
}

void stop() { gSeqPlay = false; }

void increaseBPM(int direction) {
    setTempo((byte)between(gBPM + direction, 10, 255));
    Serial.print("Set new bpm ");
    Serial.println(gBPM);
}

void setTempo(byte bpm) {
    gBPM = between(bpm, 10, 255);
    // 4 ♬ ♬ drum per beat in 60000ms = 1min
    gTempo = 60000 / (gBPM * 4);

    // Serial.print("Set tempo ");
    // Serial.println(gTempo);
}

// unsigned int fnPattern(int val, int isInc) {
//     gSeqPatternIndex = getVal(gSeqPatternIndex, val, isInc) % MAX_PATTERNS;
//     assignCurrentPattern(gSeqPatternIndex);
//     return gSeqPatternIndex;
// }
